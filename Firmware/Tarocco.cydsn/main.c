/* ========================================

    current[mA]=1000*millivolts/(20*Rsense[mOhm])=10*millivolts for a 5 mOhm sense resistor
    current_limit[mA]=40*current_setting
    
   ======================================== */
    
#include <project.h>
#include <stdlib.h>

//#define DEBUG_INTERFACE



//the maximum amount that the integral error is allowed to grow
//change to reduce or increase the integral term effect on the system
#define ERROR_INTEGRAL_MAX      10000
//maximum output value for current limiting PI control loop
//do not change this one
#define DUTY_REDUCE_MAX         4094

//number of cpu cycles the motor has to reach the desired position afeter each step pulse
#define TIMEOUT                 2000

void ffast_itoa(volatile char a_string[7], int16_t a_number) {
    char temp;
    if(a_number<0) {
        a_string[0]='-';
        a_number=-a_number;
    }
    else a_string[0]='0';
    temp = '0';
    while(a_number>=10000) {
        a_number-=10000;
        temp++;
    }
    a_string[1] = temp;
    temp = '0';
    while(a_number>=1000) {
        a_number-=1000;
        temp++;
    }
     a_string[2]= temp;
    temp = '0';
    while(a_number>=100) {
        a_number-=100;
        temp++;
    }
    a_string[3]= temp;
    temp = '0';
    while(a_number>=10) {
        a_number-=10;
        temp++;
    }
    a_string[4]= temp;
    a_string[5]=a_number+'0';
    a_string[6]='\0';

}

typedef uint32_t fix4_28;

void fast_itoa(volatile char a_string[7], int16_t a_number) {
    if(a_number<0) {
        a_string[0]='-';
       a_number=-a_number;
    }
    else a_string[0]='0';

    fix4_28 const f1_10000 = (1 << 28) / 10000;

    // 2^28 / 10000 is 26843.5456, but 26843.75 is sufficiently close.
    fix4_28 tmp = a_number * (f1_10000 + 1) - (a_number / 4);

    for(size_t i = 1; i < 6; i++)
    {
        int digit = (int)(tmp >> 28);
        a_string[i] = '0' + (char) digit;
        tmp = (tmp & 0x0fffffff) * 10;
    }
    a_string[6] = '\0';
}

CY_ISR_PROTO(uartReceiveTransmit);
CY_ISR_PROTO(transmitUpdate);
CY_ISR_PROTO(pwmCycle);
void transmit_data();
int transmitting();

//cycle counter for motor power timeout
volatile uint16_t timeout_counter;
//uart buffer
volatile uint8_t command_ready, command_index, transmit_ready, loop_proceed;
#define COMMAND_INDEX_LENGTH (16)
volatile char command_parser[COMMAND_INDEX_LENGTH];
volatile char current_tx[7], error_tx[7];


int main() {

    int16_t millivolts=0, duty_reduce=0,error=0, error_integral=0, error_derivative=0, error_at_timeout=0, error_prev=0;
    int32_t  output=0;
    uint8_t fault_detected=0, motor_shutdown=0, timeout_flag=0;
    
    //emulated EEPROM 
    static const CYCODE uint16_t kp=2500, ki=0, kd=00;
    static const CYCODE uint8_t current_setting=255, invert_motor=0, ferror=255, uart_data=1;
    //pointers to respective EEPROM addresses
    volatile const uint16_t *eeprom_kp, *eeprom_ki, *eeprom_kd;
    volatile const uint8_t *eeprom_current_setting, *eeprom_invert_motor, *eeprom_ferror, *eeprom_uart_data;

    //UART data
    uint16_t command_value=0;
    char command_type='z';
    char command_local[5];
    
    error_Write(1);
    //Initialize quadrature decoding hardware
    Counter_1_Start();
    //192008N1
    UART_Start();
    //12-bit resolution. In phase with PWM_MOT
    ADC_Start();
    //UART transmit period timer (curently 100 transmissions per second)
    TX_SEND_Start();
    //Just the EEPROM...
    EEPROM_Start();
    //prepare gate driver for operation.  12-bit 6 kHz PWM
    sleep_Write(1);
    PWM_MOT_Start();
    
    //ISRs go here
    rxISR_StartEx(uartReceiveTransmit);
    UART_SetTxInterruptMode(0);
    txISR_StartEx(transmitUpdate);
    pwmISR_StartEx(pwmCycle);
    
    //store respective EEPROM addresses for future read operations
    eeprom_kp=&kp;
    eeprom_ki=&ki;
    eeprom_kd=&kd;
    eeprom_current_setting=&current_setting;
    eeprom_invert_motor=&invert_motor;
    eeprom_ferror=&ferror;
    eeprom_uart_data=&uart_data;
    
    CyDelay(1000);
    
#ifndef DEBUG_INTERFACE
    //"board powered" signal
    vin_Write(1);
#endif //DEBUG_INTERFACE
    
    // Enable global interrupts
    CyGlobalIntEnable;

    //reset the QED hardware counter
    Counter_1_WriteCounter(0);
    uint32_t loop_counter = 0;
    
    
    for(;;) {
        //debug_pin_Write(1);
        while (!loop_proceed) {}
        //debug_pin_Write(0);
        loop_proceed = 0; 
        loop_counter++;
        //following error exceeded
        //prevents motor runaway when encoder count direction is backwards and rises an alarm when the motor cannot reach the desired position
        if(error>*eeprom_ferror || error<-*eeprom_ferror) {
            error_Write(0);
#ifndef DEBUG_INTERFACE
            err_Write(1);
#endif //DEBUG_INTERFACE
            fault_detected=1;
        }
        //if no new step pulse is received for a number of cycles, shut down the motor, until a new step pulse is received or the motor gets out of position
        else {
            if(timeout_counter<TIMEOUT) {
                timeout_counter++;
                timeout_flag=0;
                motor_shutdown=0;
            }
            else {
                if(timeout_flag==0) {
                    error_at_timeout=error;
                    timeout_flag=1;
                    motor_shutdown=1;
                }
                if(error_at_timeout-error>3 || error_at_timeout-error<-3) timeout_counter=0;
            }
        }
        
        //gate driver error
        //undervoltage, undercurrent or overtemperature
        if(fault_Read()==0) {
            error_Write(0);
#ifndef DEBUG_INTERFACE
            vin_Write(0);
            err_Write(1);
#endif //DEBUG_INTERFACE
            fault_detected=1;
        }
        if(ovc_Read()==0) {
            error_Write(0);
#ifndef DEBUG_INTERFACE
            vin_Write(0);
            err_Write(1);
#endif //DEBUG_INTERFACE
            fault_detected=1;
        }
        
        //reset pin
        if(reset_Read()==0) {
#ifndef DEBUG_INTERFACE
            error_Write(0);
            err_Write(1);
#endif
            fault_detected=1;
        }
        
        //current limiting PI control. Calculate error and add it to the previous sum of errors
        millivolts=(ADC_GetResult16(0)>>1);
        //convert the current limit magnitude to voltage so the error can be computed using the ADC reading
        duty_reduce+=((millivolts-(*eeprom_current_setting<<2))>>3);
        if(duty_reduce>DUTY_REDUCE_MAX) duty_reduce=DUTY_REDUCE_MAX;
        else if(duty_reduce<0) duty_reduce=0;
        
        //calculate error
        error=(int16_t)Counter_1_ReadCounter();
        //calculate change in process variable to prevent derivative kickback
        error_derivative=error-error_prev;
        error_prev=error;
        //sum of errors over time
        if (motor_shutdown == 0)
            error_integral+=error;
        //limit integral error
        if(error_integral>ERROR_INTEGRAL_MAX) error_integral=ERROR_INTEGRAL_MAX;
        else if(error_integral<-ERROR_INTEGRAL_MAX) error_integral=-ERROR_INTEGRAL_MAX;
        
        //output value calculation and constraining
        output=(*eeprom_kp*error)+((*eeprom_ki*error_integral)>>7)-(*eeprom_kd*error_derivative);
        if(fault_detected) {
            PWM_MOT_WriteCompare(1);
        }
        else {
            if(*eeprom_invert_motor) {
                if(output>=0) phase_Write(1);
                else {
                    output=-output;
                    phase_Write(0);
                }
            }
            else {
                if(output>=0) phase_Write(0);
                else {
                    output=-output;
                    phase_Write(1);
                }
            }
            output = output >> 8;
            if(output>4095) output=4095;
            output-=duty_reduce;
            if(output<1) output=1;
            if(motor_shutdown) PWM_MOT_WriteCompare(1);
            else PWM_MOT_WriteCompare(output);
        }
        
        
        //parse UART data. Do not use numbers as condition for the switch
        if(command_ready==1) {
            command_type=command_parser[0];
            for(int i=0; i<5; i++) command_local[i]=command_parser[i+1];
            command_value=atoi(command_local);
            switch(command_type) {
                //PID coefficients
                case 'p':
                    EEPROM_Write((const uint8_t*)&command_value, (const uint8_t*)&kp, 2);
                break;
                case 'i':
                    EEPROM_Write((const uint8_t*)&command_value, (const uint8_t*)&ki, 2);
                break;
                case 'd':
                    EEPROM_Write((const uint8_t*)&command_value, (const uint8_t*)&kd, 2);
                break;
                //current limit value
                case 'c':
                    EEPROM_Write((const uint8_t*)&command_value, &current_setting, 1);
                break;
                //motor direction of rotation flag
                case 'r':
                    EEPROM_Write((const uint8_t*)&command_value, &invert_motor, 1);
                break;
                //maximum allowable following error
                case 'f':
                    EEPROM_Write((const uint8_t*)&command_value, &ferror, 1);
                break;
                //transmit diagnostic data flag
                case 'u':
                    EEPROM_Write((const uint8_t*)&command_value, &uart_data, 1);
                break;
                //move motor
                case '+':
                    Counter_1_WriteCounter (Counter_1_ReadCounter()+command_value);
                break;
                case '-':
                    Counter_1_WriteCounter (Counter_1_ReadCounter()-command_value);
                break;
            }
            command_ready=0;
        }
        
        if (!transmitting())
        {
            //prepare UART strings
            fast_itoa(error_tx, error+500);
            fast_itoa(current_tx, 10*millivolts);
        }
        

        if(transmit_ready) {
            transmit_ready = 0; 
            if(*eeprom_uart_data) {
                transmit_data();
            }
        }
                
    }
}

volatile uint8_t transmit_state = 0; 
volatile uint32_t transmit_index;
int transmitting()
{
    return (transmit_state != 0);
}
void transmit_data()
{
    if (!transmitting())
    {
        transmit_state = 1;
        transmit_index = 0;
        UART_SetTxInterruptMode(UART_INTR_TX_NOT_FULL);
    }
}

//string transmission begins with '$' and ends with ';'
//insert a ' ' between each string
void transmit_engine()
{
    char c;
    switch (transmit_state)
    {
    case 0:
        break;
    case 1:
        transmit_state++;
        UART_UartPutChar('$');
        break;
    case 2:
        
        if (transmit_index<6)
        {
            c = error_tx[transmit_index];
            UART_UartPutChar(c);
            transmit_index++;
        }
        else
        {
            transmit_index = 0;
            transmit_state++;
        }
        break;
    case 3:
        transmit_state++;
        UART_UartPutChar(' ');
        break;
    case 4:
        
        if (transmit_index<6)
        {
            c = current_tx[transmit_index];
            UART_UartPutChar(c);
            transmit_index++;
        }
        else
        {
            transmit_index = 0;
            transmit_state++;
        }
        break;  
    case 5:
        transmit_state = 0; 
        UART_UartPutChar(';');
        UART_SetTxInterruptMode(0);
        break;      
    }
}


//write to uart buffer
CY_ISR(uartReceiveTransmit) {
    if ((UART_GetInterruptCause() == UART_INTR_CAUSE_RX) && 
        (UART_GetRxInterruptSource() & UART_INTR_RX_NOT_EMPTY))
    {
        char c = UART_UartGetChar();
        if (c == ';')
        {
            command_parser[command_index]=c;
            command_index=0;
            command_ready=1;
        }
        else if (command_index < COMMAND_INDEX_LENGTH-1)
        {
            command_parser[command_index]=c;
            command_index++;
            command_ready=0;
        }
        UART_ClearRxInterruptSource(UART_INTR_RX_NOT_EMPTY);
    }
    else if ((UART_GetInterruptCause() == UART_INTR_CAUSE_TX) && 
            (UART_GetTxInterruptSource() & UART_INTR_TX_NOT_FULL))
    {
        transmit_engine();
        UART_ClearTxInterruptSource(UART_INTR_TX_NOT_FULL);
    }
}

//set UART transmission allowed flag
CY_ISR(transmitUpdate) {
    txISR_ClearPending();
    transmit_ready=1;
}

CY_ISR_PROTO(pwmCycle) {
    PWM_MOT_ClearInterrupt(PWM_MOT_INTR_MASK_TC);
    loop_proceed=1;
}


/* [] END OF FILE */

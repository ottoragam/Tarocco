/* ========================================

    current[mA]=1000*millivolts/(20*Rsense[ohm])=5*millivolts
    current_limit[mA]=40*current_setting
    
   ======================================== */
    
#include <project.h>
#include <stdlib.h>

//the maximum amount that the integral error is allowed to grow
//change to reduce or increase the integral term effect on the system
#define ERROR_INTEGRAL_MAX      10000
//maximum output value for current limiting PI control loop
//do not change this one
#define DUTY_REDUCE_MAX         4094
//how many encoder counts per step pulse
#define SET_POINT_MULTIPLIER    1
//number of cpu cycles the motor has to reach the desired position afeter each step pulse
#define TIMEOUT                 20000

int fast_itoa(char a_string[7], int16_t a_number) {
    if(a_number<0) {
        a_string[0]='-';
        a_number=-a_number;
    }
    else a_string[0]='0';
    a_string[1]=0;
    while(a_number>=10000) {
        a_number-=10000;
        a_string[1]++;
    }
    a_string[2]=0;
    while(a_number>=1000) {
        a_number-=1000;
        a_string[2]++;
    }
    a_string[3]=0;
    while(a_number>=100) {
        a_number-=100;
        a_string[3]++;
    }
    a_string[4]=0;
    while(a_number>=10) {
        a_number-=10;
        a_string[4]++;
    }
    a_string[5]=a_number;
    a_string[6]='\0';
    
    for(int i=1; i<6; i++) a_string[i]+=48;
    
    return 1;
}

CY_ISR_PROTO(stepCount);
CY_ISR_PROTO(uartReceive);
CY_ISR_PROTO(transmitUpdate);

//error counter
volatile int32_t set_point;
//cycle counter for motor power timeout
volatile uint16_t timeout_counter;
//uart buffer
volatile uint8_t command_ready, command_index, transmit_ready;
volatile char command_parser[6];



int main() {

    int16_t error=0, error_integral=0, error_derivative=0, error_at_timeout=0, millivolts=0, duty_reduce=0;
    int32_t output=0, process_variable=0, process_variable_prev=0;
    uint8_t motor_shutdown=0, timeout_flag=0;
    
    //emulated EEPROM 
    static const CYCODE uint8_t kp=50, ki=10, kd=00, current_setting=60, invert_motor=0, ferror=50, uart_data=0;
    //pointers to respective EEPROM addresses
    volatile const uint8_t *eeprom_kp, *eeprom_ki, *eeprom_kd, *eeprom_current_setting, *eeprom_invert_motor, *eeprom_ferror, *eeprom_uart_data;

    //UART data
    uint8_t command_value=0;
    char command_type='z';
    char command_local[5], current_tx[7], error_tx[7];
    
    //"board powered" signal
    vin_Write(1);
    //
    QDEC_Start();
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
    rxISR_StartEx(uartReceive);
    txISR_StartEx(transmitUpdate);
    stepISR_StartEx(stepCount);
    
    //store respective EEPROM addresses for future read operations
    eeprom_kp=&kp;
    eeprom_ki=&ki;
    eeprom_kd=&kd;
    eeprom_current_setting=&current_setting;
    eeprom_invert_motor=&invert_motor;
    eeprom_ferror=&ferror;
    eeprom_uart_data=&uart_data;
    
    // Enable global interrupts
    CyGlobalIntEnable;
    
    for(;;) {
        
        //follwing error exceeded
        //prevents motor runaway when encoder count direction is backwards and rises an alarm when the motor cannot reach the desired position
        if(error>*eeprom_ferror || error<-*eeprom_ferror) {
            error_Write(0);
            err_Write(1);
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
                if(error_at_timeout-error>2 || error_at_timeout-error<-2) timeout_counter=0;
            }
        }
        
        //gate driver error
        //undervoltage, undercurrent or overtemperature
        if(fault_Read()==0) {}
        if(ovc_Read()==0) {}
        
        //reset pin
        if(reset_Read()==0) {
            motor_shutdown=1;
        }
        
         //current limiting PI control loop
        millivolts=(ADC_GetResult16(0)>>1);
        duty_reduce+=((millivolts-(*eeprom_current_setting<<3))>>3);
        if(duty_reduce>DUTY_REDUCE_MAX) duty_reduce=DUTY_REDUCE_MAX;
        else if(duty_reduce<0) duty_reduce=0;
        
        //calculate error
        process_variable=QDEC_GetCounter();
        error=set_point-process_variable;
        //calculate change in process variable to prevent derivative kickback
        error_derivative=process_variable-process_variable_prev;
        process_variable_prev=process_variable;
        //sum of errors over time
        error_integral+=error;
        //limit integral error
        if(error_integral>ERROR_INTEGRAL_MAX) error_integral=ERROR_INTEGRAL_MAX;
        else if(error_integral<-ERROR_INTEGRAL_MAX) error_integral=-ERROR_INTEGRAL_MAX;
        
        //output value calculation and constraining
        output=(*eeprom_kp*error)+((*eeprom_ki*error_integral)>>10)-(*eeprom_kd*error_derivative);
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
        if(output>4095) output=4095;
        output-=duty_reduce;
        if(output<1) output=1;
        if(motor_shutdown) PWM_MOT_WriteCompare(1);
        else PWM_MOT_WriteCompare(output);
        
        
        //parse UART data. Do not use numbers as condition for the switch
        if(command_ready==1) {
            command_type=command_parser[0];
            for(int i=0; i<5; i++) command_local[i]=command_parser[i+1];
            command_value=atoi(command_local);
            switch(command_type) {
                //PID coefficients
                case 'p':
                    EEPROM_Write(&command_value, &kp, 1);
                break;
                case 'i':
                    EEPROM_Write(&command_value, &ki, 1);
                break;
                case 'd':
                    EEPROM_Write(&command_value, &kd, 1);
                break;
                //currernt limit value
                case 'c':
                    EEPROM_Write(&command_value, &current_setting, 1);
                break;
                //motor direction of rotation flag
                case 'r':
                    EEPROM_Write(&command_value, &invert_motor, 1);
                break;
                //maximum allowable following error
                case 'f':
                    EEPROM_Write(&command_value, &ferror, 1);
                break;
                //transmit diagnostic data flag
                case 'u':
                    EEPROM_Write(&command_value, &uart_data, 1);
                break;
                //move motor
                case '+':
                    error+=command_value;
                break;
                case '-':
                    error-=command_value;
                break;
            }
            command_ready=0;
        }
        
        //prepare UART strings
        //fast_itoa(current_tx, 5*millivolts);
        fast_itoa(error_tx, error+4000);
        
        //string transmission begins with '$' and ends with ';'
        //insert a ' ' between each string
        if(transmit_ready) {
            if(*eeprom_uart_data) {
                UART_UartPutChar('$');
                //transmit error value
                UART_UartPutString(error_tx);
                UART_UartPutChar(' ');
                //transmit current value
                UART_UartPutString(current_tx);
                UART_UartPutChar(';');
                transmit_ready=0;
            }
        }
                
    }
}

//read step/dir input
CY_ISR(stepCount) {
    timeout_counter=0;
    if (direction_Read()) {
        set_point+=SET_POINT_MULTIPLIER;
    }
    else {
        set_point-=SET_POINT_MULTIPLIER;
    }
    step_ClearInterrupt();
}

//write to uart buffer
CY_ISR(uartReceive) {
    command_parser[command_index]=UART_UartGetChar();
    if(command_parser[command_index]!=';') {
        command_index++;
        command_ready=0;
    }
    else {
        command_index=0;
        command_ready=1;
    }
    UART_ClearRxInterruptSource(UART_INTR_RX_NOT_EMPTY);
}

//set UART transmission allowed flag
CY_ISR(transmitUpdate) {
    transmit_ready=1;
}

/* [] END OF FILE */

/* ========================================
    current[mA]=1000*millivolts/(20*Rsense)=5*millivolts
    current_limit[mA]=40*current_setting
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_INTEGRAL_MAX      4000
#define SET_POINT_MULTIPLIER    1
#define DUTY_REDUCE_MAX         4094

CY_ISR_PROTO(encoderCount);
CY_ISR_PROTO(stepCount);
CY_ISR_PROTO(uartReceive);
CY_ISR_PROTO(transmitUpdate);

//error counter
volatile int16_t error, error_prev;
//uart circular buffer
volatile uint8_t command_ready, command_index, transmit_ready;
volatile char command_parser[6];

int main()
{   
    int16_t error_integral=0, error_derivative=0, millivolts=0, duty_reduce=0;
    int32_t output=0;
    //eeprom data
    volatile const uint8_t *eeprom_kp, *eeprom_ki, *eeprom_kd, *eeprom_current_setting;
    //uart data
    static const CYCODE uint8_t kp=50, ki=1, kd=0, current_setting=127;;
    uint8_t command_value=0;
    char command_type='z';
    char command_local[5], current_tx[5], error_tx[5];
    
    //"board powered" signal
    vin_Write(1);
    
    UART_Start();
    ADC_Start();
    TX_SEND_Start();
    EEPROM_Start();
    
    //wake up gate driver
    sleep_Write(1);
    PWM_MOT_Start();
    
    rxISR_StartEx(uartReceive);
    txISR_StartEx(transmitUpdate);
    stepISR_StartEx(stepCount);
    pulseISR_StartEx(encoderCount);
    
    eeprom_kp=&kp;
    eeprom_ki=&ki;
    eeprom_kd=&kd;
    eeprom_current_setting=&current_setting;
    
    RESET_FAULT_Write(1);
    RESET_FAULT_Write(0);
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    for(;;) {
                
        //quadrature decoding invalid state
        //if(QDEC_FAULT_Read()==1) err_Write(1);
        
        //PI controller for current limiting purposes
        millivolts=ADC_CountsTo_mVolts(0, ADC_GetResult16(0));
        duty_reduce=duty_reduce+millivolts-8*(*eeprom_current_setting);
        if(duty_reduce>DUTY_REDUCE_MAX) duty_reduce=DUTY_REDUCE_MAX;
        else if(duty_reduce<0) duty_reduce=0;
        
        //calculate errors
        error_derivative=error_prev-error;
        error_prev=error;
        error_integral+=error;
        if(error_integral>ERROR_INTEGRAL_MAX) error_integral=ERROR_INTEGRAL_MAX;
        else if(error_integral<-ERROR_INTEGRAL_MAX) error_integral=-ERROR_INTEGRAL_MAX;
        
        //output scaling and constraining
        output=(*eeprom_kp)*error+(*eeprom_ki)*error_integral-(*eeprom_kd)*error_derivative;
        if(output>=0) phase_Write(1);
        else {
            output=-output;
            phase_Write(0);
        }
        output=(output>>4);
        if(output>4095) output=4095;
        output-=duty_reduce;
        if(output<1) output=1;
        PWM_MOT_WriteCompare(output);
        
        //parse command
        if(command_ready==1) {
            command_type=command_parser[0];
            for(int i=0; i<5; i++) command_local[i]=command_parser[i+1];
            command_value=atoi(command_local);
            switch(command_type) {
                case 'p':
                    EEPROM_Write(&command_value, &kp, 1);
                break;
                case 'i':
                    EEPROM_Write(&command_value, &ki, 1);
                break;
                case 'd':
                    EEPROM_Write(&command_value, &kd, 1);
                break;
                case 'c':
                    EEPROM_Write(&command_value, &current_setting, 1);
                break;
            }
            command_ready=0;
        }
        
        
        sprintf(current_tx, "%d", 5*millivolts);
        sprintf(error_tx, "%d", error+500);
                
        if(transmit_ready) {
            
            UART_UartPutChar('$');
            //transmit current value
            UART_UartPutString(current_tx);
            UART_UartPutChar(' ');
            //transmit error value
            UART_UartPutString(error_tx);
            UART_UartPutChar(';');
            
            transmit_ready=0;
        }
                
    }
}

CY_ISR(encoderCount) {
    if (QDEC_DIR_Read()==1) error++;
    else error--;
}

CY_ISR(stepCount) {
    if (direction_Read()==1) {
        error+=SET_POINT_MULTIPLIER;
        error_prev+=SET_POINT_MULTIPLIER;
    }
    else {
        error-=SET_POINT_MULTIPLIER;
        error_prev-=SET_POINT_MULTIPLIER;
    }
}

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
    UART_ClearRxInterruptSource(UART_INTR_RX_NOT_EMPTY );
}

CY_ISR(transmitUpdate) {
    transmit_ready=1;
}

/* [] END OF FILE */

/*
 * ConnectionUart.c
 *
 *  Created on: 30 gen 2023
 *      Author: simoneroman
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ConnectionUart.h>


const eUSCI_UART_ConfigV1 uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        13,                                      // BRDIV = 13
        0,                                       // UCxBRF = 0
        37,                                      // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};

uint8_t RXData = 0;
volatile int x = 0;
volatile int y = 0;
int keep_distance=0;
int mode=0;
int flag_park_ended = 0;


int getFlagParkEnded(){
    return flag_park_ended;
}

int getMode(){
    return mode;
}
int getX(){
    return x;
}

int getY(){
    return y;
}
int getKeepDistance(){
    return keep_distance;
}
int setFlagParkEnded(int flag){
    flag_park_ended=flag;
}


void configUART(){
    /* Halting WDT  */


    /* Selecting P1.2 and P1.3 in UART mode and P1.0 as output (LED) */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
             GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Setting DCO to 24MHz (upping Vcore) -> CPU operates at 24 MHz!*/
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /* Configuring UART Module */
    UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* Enable UART module */
    UART_enableModule(EUSCI_A2_BASE);

    /* Enabling interrupts */
    UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA2);
    Interrupt_enableSleepOnIsrExit();
}

/* EUSCI A0 UART ISR - Echos data back to PC host */
void EUSCIA2_IRQHandler(void){

    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);


    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        RXData = UART_receiveData(EUSCI_A2_BASE);
        //printf("ricevo:%d\n",RXData);

        if(RXData==202){
            keep_distance=1;
        }
        if(RXData==203){
            keep_distance=0;
        }


        if(RXData < 100 ) {
            x = RXData - 50;  // cordinate x da -50 a 50
            mode=0;
            flag_park_ended = 0;
        }else if(RXData < 200 ){
            y = RXData - 150; // coordinate y da -50 a 50
            mode=0;
            flag_park_ended = 0;
        }
        else if(RXData==201){
            mode=2;
        }
        else{
            mode=1;
            flag_park_ended = 0;
        }

        Interrupt_disableSleepOnIsrExit();
    }
}

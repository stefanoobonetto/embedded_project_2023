/*
 * Joystick.c
 *
 *  Created on: 26 gen 2023
 *      Author: simoneroman
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdint.h>
#include <stdbool.h>
#include <Joystick.h>
#include <Display.h>
#include <ConnectionUart.h>

volatile int semaforo = 1;   //semaforo generale per mandare la roba in UART



volatile int cont = 0;    //semaforo per mandare prima X e poi Y

volatile int sel = 0; //general selector --> for back button

//sel VALUES:
//0 --> WELCOME screen
//1 --> prima schermata di selezione
//2 --> joystick mode no kd
//3 --> joystick mode kd
//4 --> auto_park

volatile int sel1 = 0; //menu selector --> for joystick button and selector

void adcInit(){

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN1); //joystick button
   GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN1);

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); //S2 msp432
   GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1); //S2 boosterpack
   GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5); //S2 boosterpack
   GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

   //Configure P1.0
   GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

   //Configure P2.1
   GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
   GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);

   Interrupt_enableInterrupt(INT_PORT1);
   Interrupt_enableInterrupt(INT_PORT3);
   Interrupt_enableInterrupt(INT_PORT4);
   Interrupt_enableInterrupt(INT_PORT5);


   GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
   GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

   ADC14_enableModule();
   ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);

   ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
   ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

   ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

   ADC14_enableInterrupt(ADC_INT1);

   Interrupt_enableInterrupt(INT_ADC14);
   Interrupt_enableMaster();

   ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

   ADC14_enableConversion();
   ADC14_toggleConversionTrigger();
}



void PORT1_IRQHandler(void) //BACK button
{
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);

    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if(status & GPIO_PIN4){
        //sel values
        //0 --> WELCOME screen,
        //1 --> prima schermata di selezione,
        //2 --> joystick mode no kd,
        //3 --> joystick mode kd,
        //4 --> auto_park

        switch(sel){
            case 0:
                break;
            case 1:
                break;
            case 2:
                sel=1;
                graphics_first_menu(sel1);
                break;
            case 3:
                sel=1;
                graphics_first_menu(sel1);
                break;
            case 4:
                sel=1;
                graphics_first_menu(sel1);
                break;
            default:
                break;
        }
    }
}


void PORT3_IRQHandler(void){ //DOWN button

    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);

    GPIO_clearInterruptFlag(GPIO_PORT_P3, status);
    printf("secondo bottone\n");

    /*sel values
    0 --> WELCOME screen,
    1 --> prima schermata di selezione,
    2 --> joystick mode no kd,
    3 --> joystick mode kd,
    4 --> auto_park
    */

    //sel1 values
    //0 --> joystick mode no kd,
    //1 --> joystick mode kd,
    //2 --> auto_park

    if(status & GPIO_PIN5){
        switch(sel){
            case 0:
                break;
            case 1:
                switch(sel1){
                    case 0:
                        sel1 = 1;
                        draw_circle(1);
                        break;
                    case 1:
                        sel1 = 2;
                        draw_circle(2);
                        break;
                    case 2:
                        break;
                }
                break;
//            case 2:
//                break;
//            case 3:
//                break;
//            default:
                break;
            }
    }
}

void PORT4_IRQHandler(void){ //JOYSTICK SELECT
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);

    GPIO_clearInterruptFlag(GPIO_PORT_P4, status);
    printf("SONO qui\n");

    /*sel values
    0 --> WELCOME screen,
    1 --> prima schermata di selezione,
    2 --> joystick mode no kd,
    3 --> joystick mode kd,
    4 --> auto_park
    */

    //sel1 values
    //0 --> joystick mode no kd,
    //1 --> joystick mode kd,
    //2 --> auto_park

    if(status & GPIO_PIN1){
        switch(sel){
            case 0:
                break;
            case 1:
                switch(sel1){
                    case 0:
                        sel1 = 0;
                        sel = 2;
                        keep_distance(false);
                        joystick_mode_setup();
                        break;
                    case 1:
                        sel1 = 1;
                        sel = 3;
                        keep_distance(true);
                        joystick_mode_setup();
                        break;
                    case 2:
                        sel1 = 2;
                        sel = 4;
                        auto_park_mode();
                        break;
                }break;
//             case 2:
//                 break;
//             case 3:
//                 break;
//             case 4:
//                 break;
             default:
                 break;
        }
    }
}

void PORT5_IRQHandler(void){  //UP button

    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
    printf("Primo bottone\n");

    if(status & GPIO_PIN1){


        /*sel values
        0 --> WELCOME screen,
        1 --> prima schermata di selezione,
        2 --> joystick mode no kd,
        3 --> joystick mode kd,
        4 --> auto_park
        */

        //sel1 values
        //0 --> joystick mode no kd,
        //1 --> joystick mode kd,
        //2 --> auto_park

        switch(sel){
            case 0:
                sel=1;
                graphics_first_menu(sel1);
                break;
            case 1:
                switch(sel1){
                    case 0:
                        break;
                    case 1:
                        sel1 = 0;
                        draw_circle(0);
                        break;
                    case 2:
                        sel1 = 1;
                        draw_circle(1);
                        break;
                }break;
//            case 3:
//                break;
            default:
                break;
        }
    }
}

void auto_park_mode(){

   auto_park_mode_graphics();
   
    if(semaforo){
        semaforo = 0;
        while(P1IN & GPIO_PIN4){
            uint8_t auto_park = 201;                       //codice auto_park_mode = 201
            UART_transmitData(EUSCI_A2_BASE, auto_park);
        }
        semaforo = 1;
    }
}

void keep_distance(bool on){
    int contatore=0;


    if(on){
        uint8_t auto_park = 202;
        for(contatore=0;contatore<3;contatore++){//codice keep_distance_mode = 202
            UART_transmitData(EUSCI_A2_BASE, auto_park);
        }
    }
    else{
        uint8_t auto_park = 203;
        for(contatore=0;contatore<3;contatore++){//codice keep_distance_mode = 202
            UART_transmitData(EUSCI_A2_BASE, auto_park);
        }
    }



}
void joystick_mode_setup(){

    joystick_mode_graphics(sel1);

    while(P1IN & GPIO_PIN4){

        int x = (int)(ADC14_getResult(ADC_MEM0));
        int y = (int)(ADC14_getResult(ADC_MEM1));

        x = (x - 8150)/82 ; // tra -100 e 100
        y = (y - 8150)/82 ;

        x = x/2 ;
        y = y/2 ;

        x = x +  49; // tra 0 e 100 trasmetto x
        y = y + 149; // tra 100 e 200 trasmetto y

        uint8_t X = (uint8_t)x;
        uint8_t Y = (uint8_t)y;

        uint8_t v = Y-100;
        if(v >= 50){
            v -= 50;
        }else if(v < 50 && v > 43){
            v = 0;
        }else{
            v = 43 - v;
        }

        char dir[40];

        printf("y = %d\n", Y);
        if(Y < 140){
            strcpy(dir, "  retro  ");
        }else if(Y > 148){
            strcpy(dir, "forward");
        }else{
            strcpy(dir, "stalled");
        }
        draw(dir, 40, 64, 90);

        char svolta[40] = "";

        if(X < 43){
            strcat(svolta, "  left  ");
        }else if(X > 57){
            strcat(svolta, "  right  ");
        }else{
            strcat(svolta, "no turn");
        }
        draw(svolta, 40, 64, 100);

        char string[10];
        sprintf(string, "speed:");
        draw(string, 8, 64, 50);

        sprintf(string, " %d ", v);
        draw(string, 8, 64, 70);

        if(semaforo && cont){
            semaforo = 0;
            UART_transmitData(EUSCI_A2_BASE, x);
            cont = 0;
            semaforo = 1;
        }else if (semaforo && !cont){
            semaforo = 0;
            UART_transmitData(EUSCI_A2_BASE, Y);
            cont = 1 ;
            semaforo = 1;
        }
    }
}

void ADC14_IRQHandler(void)
{
    //sel values
    //0 --> WELCOME screen,
    //1 --> prima schermata di selezione,
    //2 --> joystick mode no kd,
    //3 --> joystick mode kd,
    //4 --> auto_park

    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    if(status & ADC_INT1){

    }
}

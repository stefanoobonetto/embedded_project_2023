#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdint.h>
#include <stdbool.h>
#include <Joystick.h>
#include <Display.h>
#include <ConnectionUart.h>

volatile int semaforo = 1;   //general semaphore for UART communication (just one message is sent at a time) 

volatile int cont = 0;    //semaphore to send in order first X and then Y 

volatile int sel = 0; //general selector --> for back button

//sel VALUES:
//0 --> WELCOME screen
//1 --> prima schermata di selezione
//2 --> joystick mode no anticollision
//3 --> joystick mode w/ anticollision
//4 --> auto_park

volatile int sel1 = 0; //menu selector --> for joystick button and selector

//sel1 VALUES:
//0 --> joystick mode no kd
//1 --> joystick mode kd
//2 --> auto_park

void adcInit(){

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN1); //joystick button
   GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN1);

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4); //S2 msp432
   GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1); //S1 boosterpack
   GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);

   GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5); //S2 boosterpack
   GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5);

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
           default:
                break;
            }
    }
}

void PORT4_IRQHandler(void){ //JOYSTICK SELECT
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);

    GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

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
           default:
                 break;
        }
    }
}

void PORT5_IRQHandler(void){  //UP button

    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);

    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);
   
    if(status & GPIO_PIN1){

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
           default:
                break;
        }
    }
}

void auto_park_mode(){

    clear_display_visible();

    char string[40];
    strcpy(string, "AUTO-PARK MODE");
    draw(string, 22, 64, 50);
    strcpy(string, "to interrupt the process");
    draw(string, 22, 64, 65);
    strcpy(string, "press the BACK button");
    draw(string, 22, 64, 75);

    if(semaforo){
        semaforo = 0;
        while(P1IN & GPIO_PIN4){
            uint8_t auto_park = 201;                           //auto_park_mode code = 201
            UART_transmitData(EUSCI_A2_BASE, auto_park);
        }
        semaforo = 1;
    }
}

void keep_distance(bool on){
    int contatore=0;

    if(on){
        uint8_t kd = 202;                                      //keep_distance_mode code = 202
        for(contatore=0;contatore<3;contatore++){              
            UART_transmitData(EUSCI_A2_BASE, auto_park);
        }
    }
    else{
        uint8_t kd = 203;
        for(contatore=0;contatore<3;contatore++){             
            UART_transmitData(EUSCI_A2_BASE, auto_park);
        }
    }



}

void joystick_mode_setup(){
    Graphics_clearDisplay(&sContext);
    Graphics_clearDisplay(&invisibleContext);

    Graphics_Rectangle rect1 = {1, 1, 126, 31};
    GrRectDraw(&sContext, &rect1);

    char string[25];
    sprintf(string, "JOYSTICK MODE");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 25, 64, 10, OPAQUE_TEXT);

    switch(sel1){
        case 0:
            sprintf(string, "anticollision off");
            Graphics_drawStringCentered(&sContext, (int8_t *)string, 25, 64, 22, OPAQUE_TEXT);
            break;
        case 1:
            sprintf(string, "anticollision on");
            Graphics_drawStringCentered(&sContext, (int8_t *)string, 25, 64, 22, OPAQUE_TEXT);
            break;
        default:
            break;
    }

    while(P1IN & GPIO_PIN4){
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

        int x = (int)(resultsBuffer[0]);
        int y = (int)(resultsBuffer[1]);

        x = (x - 8150)/82 ; // tra -100 e 100
        y = (y - 8150)/82 ;

        x = x/2 ;
        y = y/2 ;

        x = x +  49;         // x values = [0, 99]
        y = y + 149;         // y values = [100, 199]

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
        Graphics_drawStringCentered(&sContext, (int8_t *)dir, 40, 64, 90, OPAQUE_TEXT);

        char svolta[40] = "";

        if(X < 43){
            strcat(svolta, "  left  ");
        }else if(X > 57){
            strcat(svolta, "  right  ");
        }else{
            strcat(svolta, "no turn");
        }

        Graphics_drawStringCentered(&sContext, (int8_t *)svolta, 40, 64, 100, OPAQUE_TEXT);

        char string[10];
        sprintf(string, "speed:");
        Graphics_drawStringCentered(&sContext, (int8_t *)string, 8, 64, 50, OPAQUE_TEXT);

        sprintf(string, " %d ", v);
        Graphics_drawStringCentered(&sContext, (int8_t *)string, 8, 64, 70, OPAQUE_TEXT);

        if(semaforo && cont){
            semaforo = 0;
            UART_transmitData(EUSCI_A2_BASE, X);
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
    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    if(status & ADC_INT1){

    }
}

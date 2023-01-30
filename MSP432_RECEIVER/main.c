#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <Motor.h>
#include <UltrasonicSensor.h>
#include <ConnectionUart.h>


/**
 * main.c
 */
void main(void)
{
    WDT_A_holdTimer();

    hwInit_motori();
    configUART();
    configUltraSonic();
    avanti(0,0);

    while(1)
    {
        Interrupt_enableSleepOnIsrExit();
        PCM_gotoLPM0InterruptSafe();
        //printf("mode: %d\n", mode);
        switch(getMode()){
            case 0:

                joystickMode(getX(),getY());
                break;
            case 1:

                joystickMode(getX(),getY());
                break;
            case 2:

                parcheggioAutomatico();
                break;
            default:
                break;
        }

    }
}

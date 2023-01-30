/*
 * Motor.c
 *
 *  Created on: 30 gen 2023
 *      Author: simoneroman
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <Motor.h>
#include <UltrasonicSensor.h>
#include <ConnectionUart.h>


/* ADC results buffer */
#define EN_1_PORT  GPIO_PORT_P5
#define EN_1_PIN   GPIO_PIN6
#define IN1_1_PORT GPIO_PORT_P1
#define IN1_1_PIN  GPIO_PIN7
#define IN2_1_PORT GPIO_PORT_P5
#define IN2_1_PIN  GPIO_PIN0


#define EN_2_PORT  GPIO_PORT_P2
#define EN_2_PIN   GPIO_PIN4
#define IN1_2_PORT GPIO_PORT_P5
#define IN1_2_PIN  GPIO_PIN2
#define IN2_2_PORT GPIO_PORT_P5
#define IN2_2_PIN  GPIO_PIN7

#define AVANTI 0
#define INDIETRO 1

#define MAX_PWM 10000
#define MAX_SPEED 50



/* Timer_A Compare Configuration Parameter  (PWM) */
Timer_A_CompareModeConfig compareConfig_PWM = {
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
        5000                                        // 50% Duty Cycle
        };

/* Timer_A Up Configuration Parameter */
const Timer_A_UpModeConfig upConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,                      // SMCLK = 3 MhZ
        TIMER_A_CLOCKSOURCE_DIVIDER_12,         // SMCLK/12 = 250 KhZ
        10000,                                  // 40 ms tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
        };



void pwmEnable()
{
    /* Configures P2.4 to PM_TA0.1 for using Timer PWM to control LED */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
    GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configures P2.6 to PM_TA0.3 for using Timer PWM to control LED */
    GPIO_setAsPeripheralModuleFunctionOutputPin(EN_1_PORT, EN_1_PIN,
    GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configures P5.6 to PM_TA0.4 for using Timer PWM to control LED */
    GPIO_setAsPeripheralModuleFunctionOutputPin(EN_2_PORT, EN_2_PIN,
    GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Timer_A0 for Up Mode and starting */
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Configuring Timer_A2 for Up Mode and starting */
    Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

    /* Initialize compare registers to generate PWM */
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM); // For P2.6

    // For Port 2.4
    compareConfig_PWM.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    compareConfig_PWM.compareValue = 5000;
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM);

    // For Port 5.6
    compareConfig_PWM.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    compareConfig_PWM.compareValue = 5000;
    Timer_A_initCompare(TIMER_A2_BASE, &compareConfig_PWM);
}
void hwInit_motori()
{

    GPIO_setAsOutputPin(IN1_1_PORT, IN1_1_PIN);
    GPIO_setAsOutputPin(IN2_1_PORT, IN2_1_PIN);
    GPIO_setAsOutputPin(IN1_2_PORT, IN1_2_PIN);
    GPIO_setAsOutputPin(IN2_2_PORT, IN2_2_PIN);

    /* Initializes Clock System */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    pwmEnable();
    //Configure P1.0
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    //Configure P1.0
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    /* Halting WDT and disabling master interrupts */
    WDT_A_holdTimer();
    Interrupt_disableMaster();

    /* Set the core voltage level to VCORE1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
}

void delayManovra(int l,int r,int delay){
    int i=0;
    for(i=0;i<delay;i++){
        avanti(l,r);
    }
}

void delayRetro(int l,int r,int delay){
    int i=0;
    for(i=0;i<delay;i++){
        indietro(l,r);
    }
}

void setMotor1Direction(int direction)
{
    if (direction == 0)
    {
        // Set IN1 low and IN2 high for forward direction
        GPIO_setOutputLowOnPin(IN1_1_PORT, IN1_1_PIN);
        GPIO_setOutputHighOnPin(IN2_1_PORT, IN2_1_PIN);
    }
    else
    {
        // Set IN1 high and IN2 low for reverse direction
        GPIO_setOutputHighOnPin(IN1_1_PORT, IN1_1_PIN);
        GPIO_setOutputLowOnPin(IN2_1_PORT, IN2_1_PIN);
    }
}

void setMotor2Direction(int direction)
{
    if (direction == 0)
    {
        // Set IN1 low and IN2 high for forward direction
        GPIO_setOutputLowOnPin(IN1_2_PORT, IN1_2_PIN);
        GPIO_setOutputHighOnPin(IN2_2_PORT, IN2_2_PIN);
    }
    else
    {
        // Set IN1 high and IN2 low for reverse direction
        GPIO_setOutputHighOnPin(IN1_2_PORT, IN1_2_PIN);
        GPIO_setOutputLowOnPin(IN2_2_PORT, IN2_2_PIN);
    }
}


void setMotor1Speed(int pwm_value){
    compareConfig_PWM.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    compareConfig_PWM.compareValue = pwm_value;
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM);
}

void setMotor2Speed(int pwm_value){
    compareConfig_PWM.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    compareConfig_PWM.compareValue = pwm_value;
    Timer_A_initCompare(TIMER_A2_BASE, &compareConfig_PWM);
}

void avanti(int speedL,int speedR){  // speed from 0 to 100


    int pwm_valueL=0;
    int pwm_valueR=0;

    if(speedL > 0 ){
        setMotor1Direction(AVANTI);
        pwm_valueL = (MAX_PWM/MAX_SPEED)*speedL;


    }else{
        setMotor1Direction(INDIETRO);
        pwm_valueL = (MAX_PWM/MAX_SPEED)*(-speedL);


    }
    if(speedR > 0 ){
        setMotor2Direction(AVANTI);
        pwm_valueR = (MAX_PWM/MAX_SPEED)*speedR ;

    }else{
        setMotor2Direction(INDIETRO);
        pwm_valueR = (MAX_PWM/MAX_SPEED)*(-speedR) ;
    }


    setMotor2Speed(pwm_valueL);
    setMotor1Speed(pwm_valueR);

}

void indietro(int speedL,int speedR){
    int pwm_valueL=0;
    int pwm_valueR=0;

    if(speedL > 0 ){
        setMotor2Direction(INDIETRO);
        pwm_valueL = (MAX_PWM/MAX_SPEED)*speedL;


    }else{
        setMotor2Direction(AVANTI);
        pwm_valueL = (MAX_PWM/MAX_SPEED)*(-speedL);


    }
    if(speedR > 0 ){
        setMotor1Direction(INDIETRO);
        pwm_valueR = (MAX_PWM/MAX_SPEED)*speedR ;

    }else{
        setMotor1Direction(AVANTI);
        pwm_valueR = (MAX_PWM/MAX_SPEED)*(-speedR) ;
    }


    setMotor2Speed(pwm_valueL);
    setMotor1Speed(pwm_valueR);
}


void parcheggioAutomatico(){
    if(!getFlagParkEnded()){
        int i=0;
        int j=0;
        int k=0;
        //servoDX();
        while(i<190){
            //printf("%d\n",i);
            if(leggiDati()>20){
                i++;
            }
            else{
                printf("%d\n",i);
                k=i;
                for(j=0;j<6;j++){
                    if(leggiDati()>20){
                        k++;
                    }
                    else{
                        k--;
                    }
                }
                if(k<=i){
                    i=0;
                }
                i++;
            }
            avanti(15,15);
        }

        printf("uscito\n");


        delayManovra(0,0,20000);

        //un po'avanti
        //delayManovra(15,15,20000);
        //delayManovra(0,0,40000);
        //gira
        delayManovra(-20,0,30000);
        delayManovra(0,0,50000);
        //retro
        delayRetro(15,15,20000);
        delayManovra(0,0,50000);

        //rigira
        delayManovra(0,-20,30000);

        setFlagParkEnded(1);
    }
    avanti(0,0);
    //servoDRITTO();
}

void joystickMode(int x,int y){
    int ml,mr;

    if(getKeepDistance()){
        if(leggiDati()<20){

            if(y<=-10){

                if(x>=0){
                    ml = -y;
                    mr = -y-x;
                }else{
                    mr = -y;
                    ml =-y+x;
                }
                indietro(ml,mr);

            }else{
                avanti(0,0);

            }
        }
        else{
            if(y>=10){

                if(x>=0){
                    ml = y;
                    mr = y-x;
                }else{
                    mr = y;
                    ml = y+x;
                }
                printf("ml : %d \n",ml);
                printf("mr : %d \n",mr);
                avanti(ml,mr);

            }else if(y<=-10){

                if(x>=0){
                    ml = -y;
                    mr = -y-x;
                }else{
                    mr = -y;
                    ml =-y+x;
                }
                indietro(ml,mr);

            }else{
                avanti(0,0);

            }
        }
    }

    else{
        if(y>=10){

            if(x>=0){
                ml = y;
                mr = y-x;
            }else{
                mr = y;
                ml = y+x;
            }
            printf("ml : %d \n",ml);
            printf("mr : %d \n",mr);
            avanti(ml,mr);

        }else if(y<=-10){

            if(x>=0){
                ml = -y;
                mr = -y-x;
            }else{
                mr = -y;
                ml =-y+x;
            }
            indietro(ml,mr);

        }else{
            avanti(0,0);

        }
    }

}




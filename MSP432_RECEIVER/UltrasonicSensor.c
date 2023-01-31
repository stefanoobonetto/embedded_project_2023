/*
 * UltrasonicSensor.c
 *
 *  Created on: 30 gen 2023
 *      Author: simoneroman
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <UltrasonicSensor.h>

//Ultrasonic sensor
#define TRIGGER_PIN BIT6
#define ECHO_PIN BIT7


void configUltraSonic(){
    // Configure trigger pin as output
    P2DIR |= TRIGGER_PIN;
    P2OUT &= ~TRIGGER_PIN;

    // Configure echo pin as input
    P2DIR &= ~ECHO_PIN;
    P2REN |= ECHO_PIN;
}

uint32_t leggiDati(){


    // Send trigger pulse
    P2OUT |= TRIGGER_PIN;
    __delay_cycles(10);
    P2OUT &= ~TRIGGER_PIN;

    // Wait for echo
    while (!(P2IN & ECHO_PIN));


    // Start timer
    //TASSEL_1-> ACLK clock.    MC_2->Continous mode
    TA1CTL = TASSEL_1 + MC_2 + TACLR;

    // Wait for echo to end
    while (P2IN & ECHO_PIN);

    // Stop timer
    TA1CTL = MC_0;

    // Calculate distance
    uint32_t distance = ((TA1R));
    distance= (distance+7)/2;
    printf("distance %u\n",distance);

    return distance;

}

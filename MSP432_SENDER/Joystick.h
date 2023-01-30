/*
 * Joystick.h
 *
 *  Created on: 26 gen 2023
 *      Author: simoneroman
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_


void adcInit();
void ADC14_IRQHandler();
void joystick_mode_setup();
void keep_distance(bool on);
void auto_park_mode();
void PORT4_IRQHandler(void);
void PORT3_IRQHandler(void);
void PORT5_IRQHandler(void);
void PORT1_IRQHandler(void);


#endif /* JOYSTICK_H_ */

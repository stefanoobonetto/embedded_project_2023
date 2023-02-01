/*
 * Motor.h
 *
 *  Created on: 30 gen 2023
 *      Author: simoneroman
 */

#ifndef MOTOR_H_
#define MOTOR_H_




void init_pwm();
void hwInit_motori();
void setMotor1Direction(int direction);
void setMotor2Direction(int direction);
void setMotor1Speed(int pwm_value);
void setMotor2Speed(int pwm_value);
void avanti(int speedL,int speedR);
void indietro(int speedL,int speedR);
void parcheggioAutomatico();
void joystickMode(int x,int y);


#endif /* MOTOR_H_ */

/*
 * ConnectionUart.h
 *
 *  Created on: 30 gen 2023
 *      Author: simoneroman
 */

#ifndef CONNECTIONUART_H_
#define CONNECTIONUART_H_


void configUART();
void EUSCIA2_IRQHandler(void);
int getMode();
int getX();
int getY();
int getKeepDistance();
int getFlagParkEnded();
int setFlagParkEnded(int flag);


#endif /* CONNECTIONUART_H_ */

/*
 * Display.h
 *
 *  Created on: 26 gen 2023
 *      Author: simoneroman
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_


void graphicsInit();
void draw(char string[],int x,int y,int z);
void clear_display_visible();
void clear_display_invisible();
void draw_circle(int choice);
void graphics_first_menu();



#endif /* DISPLAY_H_ */

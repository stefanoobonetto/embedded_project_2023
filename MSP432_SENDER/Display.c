/*
 * Display.c
 *
 *  Created on: 26 gen 2023
 *      Author: simoneroman
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <Display.h>
#include <string.h>

Graphics_Context sContext;
Graphics_Context invisibleContext;

void draw(char string[],int length,int x,int y){     //allows functions in Joystick.c to draw strings in the display
    Graphics_drawStringCentered(&sContext, (int8_t *)string, length, x, y, OPAQUE_TEXT);
}

void graphicsInit()
{
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    Graphics_initContext(&sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_initContext(&invisibleContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    Graphics_setForegroundColor(&invisibleContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&invisibleContext, GRAPHICS_COLOR_WHITE);
    Graphics_setForegroundColor(&sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&sContext);
    Graphics_clearDisplay(&invisibleContext);


    char string[100];
    strcpy(string, "WELCOME :)");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 40, OPAQUE_TEXT);
    strcpy(string, "this is a project by");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 55, OPAQUE_TEXT);
    strcpy(string, "Stefano Bonetto");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 65, OPAQUE_TEXT);
    strcpy(string, "Mattia Rigon");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 75, OPAQUE_TEXT);
    strcpy(string, "Simone Roman");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 85, OPAQUE_TEXT);
    strcpy(string, "press S1 to start");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 100, OPAQUE_TEXT);

}

void draw_circle(int choice){  //draw the circle corresponding to choice (0, 1, 2) as the selector for the menu
    switch (choice)
    {
    case 0:
        Graphics_fillCircle(&sContext, 20, 25, 5);
        Graphics_fillCircle(&invisibleContext, 20, 64, 5);
        Graphics_fillCircle(&invisibleContext, 20, 103, 5);
        break;

    case 1:
        Graphics_fillCircle(&invisibleContext, 20, 25, 5);
        Graphics_fillCircle(&sContext, 20, 64, 5);
        Graphics_fillCircle(&invisibleContext, 20, 103, 5);
        break;

    case 2:
        Graphics_fillCircle(&invisibleContext, 20, 25, 5);
        Graphics_fillCircle(&invisibleContext, 20, 64, 5);
        Graphics_fillCircle(&sContext, 20, 103, 5);
        break;


    default:
        break;
    }
}

void graphics_first_menu(int sel1){    

    Graphics_clearDisplay(&sContext);
    GrClearDisplay(&invisibleContext);

    Graphics_Rectangle rect1 = {5, 10, 123, 40};
    Graphics_Rectangle rect2 = {5, 49, 123, 79};
    Graphics_Rectangle rect3 = {5, 88, 123, 118};
    Graphics_Rectangle quad1 = {10, 15, 30, 35};
    Graphics_Rectangle quad2 = {10, 54, 30, 74};
    Graphics_Rectangle quad3 = {10, 93, 30, 113};

    GrRectDraw(&sContext, &rect1);
    GrRectDraw(&sContext, &rect2);
    GrRectDraw(&sContext, &rect3);

    GrRectDraw(&sContext, &quad1);
    GrRectDraw(&sContext, &quad2);
    GrRectDraw(&sContext, &quad3);

    GrFlush(&sContext);

    char string[3][40];
    strcpy(string[0], "joystick mode");
    Graphics_drawString(&sContext, (int8_t *)string[0], 22, 35, 22, OPAQUE_TEXT);
    strcpy(string[1], "anticollision");
    Graphics_drawString(&sContext, (int8_t *)string[1], 22, 35, 61, OPAQUE_TEXT);
    strcpy(string[2], "autopark mode");
    Graphics_drawString(&sContext, (int8_t *)string[2], 22, 35, 100, OPAQUE_TEXT);

    switch(sel1){
        case 0:
            Graphics_fillCircle(&sContext, 20, 25, 5);
            Graphics_fillCircle(&invisibleContext, 20, 64, 5);
            Graphics_fillCircle(&invisibleContext, 20, 103, 5);
            break;
        case 1:
            Graphics_fillCircle(&invisibleContext, 20, 25, 5);
            Graphics_fillCircle(&sContext, 20, 64, 5);
            Graphics_fillCircle(&invisibleContext, 20, 103, 5);
            break;
        case 2:
            Graphics_fillCircle(&invisibleContext, 20, 25, 5);
            Graphics_fillCircle(&invisibleContext, 20, 64, 5);
            Graphics_fillCircle(&sContext, 20, 103, 5);
            break;
    }

}

void joystick_mode_graphics(int sel1){
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
}

void auto_park_mode_graphics(){
    Graphics_clearDisplay(&sContext);
    Graphics_clearDisplay(&invisibleContext);

    char string[40];
    strcpy(string, "AUTO-PARK MODE");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 50, OPAQUE_TEXT);
    strcpy(string, "press BACK button");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 65, OPAQUE_TEXT);
    strcpy(string, "to exit");
    Graphics_drawStringCentered(&sContext, (int8_t *)string, 22, 64, 75, OPAQUE_TEXT);
}

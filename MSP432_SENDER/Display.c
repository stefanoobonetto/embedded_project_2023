#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdint.h>
#include <stdbool.h>
#include <Display.h>

Graphics_Context sContext;
Graphics_Context invisibleContext;

void clear_display_visible(){
    Graphics_clearDisplay(&sContext);
}

void clear_display_invisible(){
    Graphics_clearDisplay(&invisibleContext);
}

void draw(char string[],int x,int y,int z){
    Graphics_drawStringCentered(&sContext, (int8_t *)string, x, y, z, OPAQUE_TEXT);
}

void draw_rectangle(int v1,int v2,int v3,int v4){
    Graphics_Rectangle rect1 = {v1, v2, v3, v4};
    GrRectDraw(&sContext, &rect1);
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
    clear_display_visible();
    clear_display_invisible();
    
    char string[100];
    strcpy(string, "WELCOME :)");
    draw(string, 22, 64, 40);
    strcpy(string, "this is a project by");
    draw(string, 22, 64, 55);
    strcpy(string, "Stefano Bonetto");
    draw(string, 22, 64, 65);
    strcpy(string, "Mattia Rigon");
    draw(string, 22, 64, 75);
    strcpy(string, "Simone Roman");
    draw(string, 22, 64, 85);
    strcpy(string, "press S1 to start");
    draw(string, 22, 64, 100);
}

void draw_circle(int choice){
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
    // pallino 1 quadrato


void graphics_first_menu(int sel1){

    Graphics_clearDisplay(&sContext);
    GrClearDisplay(&invisibleContext);
    sel = 1;

    //second screen elements
    draw_rectangle(5, 10, 123, 40);
    draw_rectangle(5, 49, 123, 79);
    draw_rectangle(5, 88, 123, 118);
    draw_rectangle(10, 15, 30, 35);
    draw_rectangle(10, 54, 30, 74);
    draw_rectangle(10, 93, 30, 113);

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



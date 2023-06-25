/*****************************************************************************
* | File      	:   OLED_1in3_test.c
* | Author      :
* | Function    :
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/
//#include "Debug.h"
//#include <stdlib.h>
#include <iostream>
#include "DEV_Config.h"
#include "menu.hpp"

const int NUM_MENU_ITEMS = 2;
int selectedMenuItem = 0;
int prevMenuItem = -1;

void handleUpButton()
{
    selectedMenuItem = (selectedMenuItem + NUM_MENU_ITEMS - 1) % NUM_MENU_ITEMS;
}

void handleDownButton()
{
    selectedMenuItem = (selectedMenuItem + 1) % NUM_MENU_ITEMS;
}

int main(void)
{

    DEV_Delay_ms(100);

    if (DEV_Module_Init() != 0)
    {
        while (1)
        {
            printf("END\r\n");
        }
    }

    /* Init */
    OLED_1in3_C_Init();
    OLED_1in3_C_Clear();

    UBYTE *BlackImage;
    UWORD Imagesize = ((OLED_1in3_C_WIDTH % 8 == 0) ? (OLED_1in3_C_WIDTH / 8) : (OLED_1in3_C_WIDTH / 8 + 1)) * OLED_1in3_C_HEIGHT;
    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
    {
        while (1)
        {
            printf("Failed to apply for black memory...\r\n");
        }
    }

    Paint_NewImage(BlackImage, OLED_1in3_C_WIDTH, OLED_1in3_C_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);

    Paint_Clear(BLACK);

    Welcome_Msg_0 m0 = Welcome_Msg_0("Glucose", "Monitoring", "System");
    m0.Display_Message();

    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(1000);

    Paint_Clear(BLACK);

    Welcome_Msg_1 m1 = Welcome_Msg_1("By:", "Swaleh Hussein", "MCTY | MSc. | IoT", "DCU Student No:", "21270106");
    m1.Display_Message();

    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(1000);

    Paint_Clear(BLACK);

    Welcome_Msg_2 m2 = Welcome_Msg_2("Device Init", BlackImage);
    m2.Display_Message();

    Paint_Clear(BLACK);

    int key0 = 15;
    int key1 = 17;
    int key = 0;
    DEV_GPIO_Mode(key0, 0);
    DEV_GPIO_Mode(key1, 0);

    int Items[2][2] = {{14, 37}, {40, 62}};

    const unsigned char *graphicArray[2] = { Graphicx[0], Graphicx[1]};
    Menu_0 menu0 = Menu_0("Main menu:", "Pair Bluetooth", "Dashboard", graphicArray);
    menu0.Display_Menu();

    OLED_1in3_C_Display(BlackImage);

    while (1)
    {
        if (DEV_Digital_Read(key0) == 0)
        {
            handleUpButton();
            while (gpio_get(key0) == 0)
            {
                tight_loop_contents();
            }
        }
        else if (DEV_Digital_Read(key1) == 0)
        {
            handleDownButton();
            while (gpio_get(key1) == 0)
            {
                tight_loop_contents();
            }
        }

        if (selectedMenuItem != prevMenuItem)
        {
            // Update the display only when the selected menu item changes
            Paint_Clear(BLACK);

            Paint_DrawString_EN(1, 1, "Main menu:", &Font12, WHITE, BLACK);
            Paint_DrawLine(0, 12, 128, 12, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

            // Draw the "Pair Bluetooth" menu item
            if (selectedMenuItem == 0)
            {
                // Draw a rectangle around the selected menu item
                Paint_DrawRectangle(1, 14, 127, 37, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
            }
            Paint_DrawString_EN(26, 21, "Pair Bluetooth", &Font12, WHITE, BLACK);
            Paint_BmpWindows(5, 16, Graphicx[0], 21, 21);

            // Draw the "Dashboard" menu item
            if (selectedMenuItem == 1)
            {
                // Draw a rectangle around the selected menu item
                Paint_DrawRectangle(1, 40, 127, 62, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
            }
            Paint_DrawString_EN(26, 46, "Dashboard", &Font12, WHITE, BLACK);
            Paint_BmpWindows(2, 42, Graphicx[1], 21, 20);

            OLED_1in3_C_Display(BlackImage);

            prevMenuItem = selectedMenuItem;
        }
    }

    return 0;
}
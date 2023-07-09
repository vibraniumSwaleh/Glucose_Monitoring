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
// #include "Debug.h"
// #include <stdlib.h>
#include <iostream>
#include "DEV_Config.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "menu.hpp"

#define ADC_CHANNEL_TEMPSENSOR 4

// core 1 main code
void core1_entry()
{
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
    }
    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}

double poll_temp(void) {
    adc_select_input(ADC_CHANNEL_TEMPSENSOR);
    uint32_t raw32 = adc_read();
    uint16_t current_temp;
    const uint32_t bits = 12;

    // Scale raw reading to 16 bit value using a Taylor expansion (for 8 <= bits <= 16)
    uint16_t raw16 = raw32 << (16 - bits) | raw32 >> (2 * bits - 16);

    // ref https://github.com/raspberrypi/pico-micropython-examples/blob/master/adc/temperature.py
    const float conversion_factor = 3.3 / (65535);
    float reading = raw16 * conversion_factor;
    
    // The temperature sensor measures the Vbe voltage of a biased bipolar diode, connected to the fifth ADC channel
    // Typically, Vbe = 0.706V at 27 degrees C, with a slope of -1.721mV (0.001721) per degree. 
    double deg_c = 27 - (reading - 0.706) / 0.001721;
    current_temp = deg_c * 100;
    printf("Write temp %.2f degc\n", deg_c);
    return deg_c;
 }

int main(void)
{
    stdio_init_all();
    // start core 1
    multicore_launch_core1(core1_entry);

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
    m0.Display_Message(BlackImage);
    DEV_Delay_ms(1000);

    Paint_Clear(BLACK);

    Welcome_Msg_1 m1 = Welcome_Msg_1("By:", "Swaleh Hussein", "MCTY | MSc. | IoT", "DCU Student No:", "21270106");
    m1.Display_Message(BlackImage);
    DEV_Delay_ms(1000);

    Paint_Clear(BLACK);

    Welcome_Msg_2 m2 = Welcome_Msg_2("Device Init");
    m2.Display_Message(BlackImage);

    Paint_Clear(BLACK);

    // int key0 = 15;
    // int key1 = 17;

    // Initialise adc for the temp sensor
    adc_init();
    adc_select_input(ADC_CHANNEL_TEMPSENSOR);
    adc_set_temp_sensor_enabled(true);

    const unsigned char *graphicArray[5] = {Graphicx[0], Graphicx[1], Graphicx[2], Graphicx[3], Graphicx[4]};

    while (true)
    {
        double blood_sugar_reading = poll_temp();

        Paint_DrawNum(32, 21, blood_sugar_reading, &Font24, 2, BLACK, WHITE);
        Paint_DrawString_EN(86, 42, "mmol/L", &Font8, WHITE, BLACK);
        Paint_BmpWindows(108, 5, graphicArray[4], 15, 15);
        OLED_1in3_C_Display(BlackImage);
        DEV_Delay_ms(5000);

        Paint_Clear(BLACK);
        OLED_1in3_C_Display(BlackImage);
    }
    
    return 0;
}






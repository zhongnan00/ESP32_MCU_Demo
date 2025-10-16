/**
 * @file oled.cpp
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <U8g2lib.h>
#include "oled.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//pixels: 72x40


// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* reset=*/ 4);
//# IIC version
U8G2_SSD1306_72X40_ER_1_SW_I2C u8g2(U8G2_R0,6,5,U8X8_PIN_NONE); 
//ESP32C3 OLED开发板的屏幕接线：scl-->gpio6  sda-->gpio5 
//如果是Arduino则改为scl-->A5  sda-->A4

void oled_init(void)
{
    u8g2.setContrast(250);
    u8g2.begin();

}

void oled_clear(void)
{
    u8g2.clearDisplay();

}

void oled_task_run(void* arg)
{
    oled_init(); 
    u8g2.firstPage();
    do {
        // u8g2.clearBuffer();

        u8g2.setFont(u8g2_font_6x10_tr);
        u8g2.drawStr(0, 10, "SN:24T00014");
        u8g2.drawStr(0, 20, "P : 10 mmHg");
        u8g2.drawStr(0, 30, "T : 36.5 oC");
        u8g2.drawStr(0, 40, "[ 80%][BLE]");
        u8g2.sendBuffer();
    } while ( u8g2.nextPage() );

}


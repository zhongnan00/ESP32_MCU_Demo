/**
 * @file tft_lcd.cpp
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "tft_lcd.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_SCLK    2 //SCK
#define TFT_MOSI    3 //SDA
#define TFT_RST     10 //RES
#define TFT_DC      6  //DC
#define TFT_CS      7  //CS
// #define TFT_BL      5  //not connected


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
void tft_lcd_init(void)
{
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_RED);
    tft.setTextColor(ST7735_YELLOW);
    tft.setTextSize(2);
    tft.setCursor(10, 30);
    tft.print("Hello ST7735!");

}
    
void tft_lcd_clear(void)
{

}

void tft_lcd_task_run(void* arg)
{

}
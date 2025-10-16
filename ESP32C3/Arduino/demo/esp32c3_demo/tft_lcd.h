/**
 * @file tft_lcd.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _TFT_LCD_H_
#define _TFT_LCD_H_

void tft_lcd_init(void);   //spi
    
void tft_lcd_clear(void);

void tft_lcd_task_run(void* arg);


#endif // _TFT_LCD_H_
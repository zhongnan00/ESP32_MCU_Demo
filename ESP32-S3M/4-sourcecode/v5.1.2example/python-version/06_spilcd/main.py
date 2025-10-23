"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    0.96寸TFTLCD实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习0.96寸TFTLCD的使用
 *
 * 硬件资源及引脚分配： 
 * 1, 0.96寸tftlcd
 *
 * 实验现象
 * 1, 刷新颜色。
 * 
 * 注意事项
 * 无
 * 
 ******************************************************************************
 * 
 * 实验平台:正点原子 ESP32-S3 最小系统板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
"""

from machine import Pin,SPI
import st7735
import time


"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == '__main__':
    
    x = 0  # Initialize variable x to 0
    spi = SPI(2, baudrate=80000000, sck=Pin(12), mosi=Pin(11), miso=Pin(13))
    tft = st7735.atk_tft(spi,40,38,39,41,rotate = 1) #DC, Reset, CS, BL, rotate
    #tft.bmp('flower64x48.bmp',10,10,1)
    #time.sleep(3)   # Sleep execution for 3 second
    
    while True:                             # Start an infinite loop
        
        # Create a dictionary for different LCD colors
        seasondict = {
            0: st7735.BLACK,
            1: st7735.BLUE,
            2: st7735.RED,
            3: st7735.GREEN,
            4: st7735.CYAN,
            5: st7735.YELLOW,
            6: st7735.WHITE}

        # Refresh the LCD display with the current color
        tft.clear(seasondict[x])                                    # Clear the display with the color indexed by x
        tft.p_string(0,0,"ESP32-S3")
        tft.p_string(0,12,"ATOM@ALIENTEK")
        x += 1          # Increment x by 1
        
        if x == 7:      # If x reaches 7, reset it to 0
            x = 0
        time.sleep(1)   # Sleep execution for 1 second


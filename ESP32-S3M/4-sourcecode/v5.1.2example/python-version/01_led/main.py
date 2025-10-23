"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    LED实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：如何点亮一个LED
 *
 * 硬件资源及引脚分配： 
 * 1, LED --> ESP32S3 IO
 *    LED --> IO1
 * 
 * 实验现象
 * 1, LED每500ms进行闪烁。
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

from machine import Pin
import time


"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if  __name__ == '__main__':
    
    # 初始化LED并输出高电平
    led = Pin(1,Pin.OUT,value = 1)
    
    while True:
        
        led.value(0)                    # 设置GPIO1输出低电平
        time.sleep_ms(500)              # 延时500ms
        led.value(1)                    # 设置GPIO1输出高电平
        time.sleep_ms(500)              # 延时500ms


"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    看门狗实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习独立看门狗的使用
 *
 * 硬件资源及引脚分配： 
 * 1,    LED  --> ESP32S3 IO
 *       LED  --> IO1
 * 2,    KEY  --> ESP32S3 IO
 *       BOOT --> IO0
 *
 * 实验现象
 * 1, 如果看门狗没有复位，开发板的LED将常亮，如果BOOT按键按下，就喂狗，
 *    只要BOOT不停的按，看门狗就一直不会产生复位，保持LED的常亮，一旦超过看门狗
 *    溢出时间还没按，那么将会导致程序重启，这将导致LED熄灭一次,看起来就是LED在闪烁。
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

from machine import Pin,I2C,WDT
import time


"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == '__main__':
    
    # 初始化LED并输出高电平
    led = Pin(1,Pin.OUT,value = 1)
    time.sleep_ms(1000)
    # 看门狗初始化，定时时间为3s
    wdt = WDT(timeout=3000)
    led.value(0)
    
    while True:
        if key.value() == 0:                # 判断KEY是否按下
            
            time.sleep_ms(10)               # 该延时为按键消抖
            
            if key.value() == 0:            # 再一次判断是否按下
                # 喂狗
                wdt.feed()
                
                while not key.value():      # 检测按键是否松开
                    pass

        time.sleep_ms(10)                   # 延时10ms

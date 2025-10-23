"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    PWM实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习PWM输出功能
 *
 * 硬件资源及引脚分配： 
 * 1, LED --> ESP32S3 IO
 *    LED --> IO1
 * 
 * 实验现象
 * 1, LED0由暗变亮，再从亮变暗，依次循环。
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

from machine import Pin,PWM
import time


"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == '__main__':
    
    pwm = PWM(Pin(1),freq = 1000)
    
    while True:
        # 渐亮
        for i in range(0,1024):
            pwm.duty(i)
            time.sleep_ms(1)
            
        # 渐暗
        for i in range(1023,0,-1):
            pwm.duty(i)
            time.sleep_ms(1)

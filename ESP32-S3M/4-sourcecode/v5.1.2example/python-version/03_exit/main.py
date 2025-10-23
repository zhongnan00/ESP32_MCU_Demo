"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    外部中断实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习外部中断的使用
 *
 * 硬件资源及引脚分配： 
 * 1, LED  --> ESP32S3 IO
 *    LED  --> IO1
 * 2, KEY  --> ESP32S3 IO
 *    BOOT --> IO0
 *
 * 实验现象
 * 1, 按下BOOT按键可控制LED0状态翻转。
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
 * @brief       按键中断服务函数
 * @param       key:定时器句柄
 * @retval      无
"""
def KEY_INT_IRQHandler(key):
    
    time.sleep_ms(10)                           # 按键消抖
    
    if key.value() == 0:
        global led_state
        led_state = led.value()
        led.value(not led_state)

"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == '__main__':
    
    # 初始化LED并输出高电平
    led = Pin(1,Pin.OUT,value = 1)
    # 配置key引脚模式及上下拉
    key = Pin(0,Pin.IN,Pin.PULL_UP)
    # 定义中断，下降沿触发
    key.irq(KEY_INT_IRQHandler,Pin.IRQ_FALLING)
    # 主循环，防止程序退出
    while True:
        pass
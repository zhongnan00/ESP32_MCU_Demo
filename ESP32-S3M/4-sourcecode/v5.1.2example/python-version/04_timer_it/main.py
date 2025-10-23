"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    定时器中断实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习定时器中断
 *
 * 硬件资源及引脚分配： 
 * 1, LED --> ESP32S3 IO
 *    LED --> IO1
 * 
 * 实验现象
 * 1, 定时器每1秒钟控制LED状态翻转。
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

from machine import Pin,Timer
import time


"""
 * @brief       基本定时器TIMEX中断服务函数
 * @param       tim:定时器句柄
 * @retval      无
"""
def BTMR_TIMEX_INT_IRQHandler(tim):
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
    # 开启定时器1
    tim = Timer(1)
    # 配置定时器1：1000ms中断、循环模式及中断回调函数BTMR_TIMEX_INT_IRQHandler
    tim.init(period = 1000, mode = Timer.PERIODIC,callback = BTMR_TIMEX_INT_IRQHandler)

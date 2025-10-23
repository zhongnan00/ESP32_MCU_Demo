"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    RTC实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习ESP32-S3片内RTC的使用
 *
 * 硬件资源及引脚分配： 
 * 1,     LED --> ESP32S3 IO
 *        LED --> IO1
 * 2,  XL9555 --> ESP32S3 IO
 *        SCL --> IO42
 *        SDA --> IO41
 *        INT --> IO0(跳线帽连接) 
 * 3, SPI_LCD --> ESP32S3 IO / XL9555
 *         CS --> IO21
 *        SCK --> IO12
 *        SDA --> IO11
 *         DC --> IO40(跳线帽连接)
 *        PWR --> XL9555_P13
 *        RST --> XL9555_P12
 *
 * 实验现象
 * 1, 通过LCD实时显示RTC时间。
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

from machine import Pin,RTC,SPI,I2C
import st7735
import time


"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == '__main__':
    
    # 初始化LED并输出高电平
    led = Pin(1,Pin.OUT,value = 1)
    spi = SPI(2, baudrate=80000000, sck=Pin(12), mosi=Pin(11), miso=Pin(13))
    tft = st7735.atk_tft(spi,40,38,39,41,rotate = 1) #DC, Reset, CS, BL, rotate
    time.sleep_ms(100)
    # 显示实验信息
    tft.p_string(0,0,"ESP32-S3")
    tft.p_string(0,12,"ATOM@ALIENTEK")
    tft.p_string(0,24, "Specific:")
    tft.p_string(0,36, "Time:")
    tft.p_string(0,48, "Date:")
    # 初始化RTC
    rtc = RTC()
    
    if rtc.datetime()[0] != 2023:
        rtc.datetime((2023, 8, 15, 2, 0, 0, 0, 0))
    
    while True:

        data_time = rtc.datetime()
        tft.p_string(60, 24, str(data_time[0:3]))
        tft.p_string(30, 36, str(data_time[4:7]))
        tft.p_string(30, 48, str(int(data_time[3]) + 1))

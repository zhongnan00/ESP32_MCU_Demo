"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    SD实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：如何驱动SD卡，并实现读写操作
 *
 * 硬件资源及引脚分配： 
 * 1,   SD --> ESP32S3 IO
 *    SDCS --> IO2
 *     SCK --> IO12
 *    MOSI --> IO11
 *    MISO --> IO13
 *
 * 实验现象
 * 1, 本实验代码,首先读取挂载SD卡前的系统文件目录，挂载成功之后再次读取系统文件目录，此时系统文件目录包含了sd卡文件夹，接着对SD卡的文件进行读写操作。
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

from machine import Pin,SPI,I2C
from sdcard import SDCard
import st7735
import time
import uos

"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == '__main__':
    
    x = 0
    # IIC初始化
    i2c0 = I2C(0, scl = Pin(42), sda = Pin(41), freq = 400000)
    spi = SPI(2, baudrate=80000000, sck=Pin(12), mosi=Pin(11), miso=Pin(13))
    tft = st7735.atk_tft(spi,40,38,39,41,rotate = 1) #DC, Reset, CS, BL, rotate
    sd = SDCard(spi,Pin(2,Pin.OUT))
    # 实验信息
    tft.p_string(0,0,"ESP32-S3")
    tft.p_string(0,12,"ATOM@ALIENTEK")
    tft.p_string(0,24,"File Read:")
    # 挂在到SD/sd
    uos.mount(sd,'/sd')
    # 重新查询系统文件目录
    print('挂载SD后的系统目录:{}'.format(uos.listdir()))
    with open("/sd/test.txt", "w") as f:
            f.write(str("Hello ALIENTEK"))

    # 从sd卡目录下读取hello.txt文件内容
    with open("/sd/test.txt", "r") as f:
        # 打印读取的内容
        data = f.read()
    
    tft.p_string(60, 24, str(data))
    # 卸載SD卡  
    uos.umount('/sd')
    
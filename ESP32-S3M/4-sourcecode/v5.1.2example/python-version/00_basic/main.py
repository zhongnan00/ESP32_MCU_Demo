"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    基础工程
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：查看ESP32-S3内部资源
 *
 * 硬件资源及引脚分配
 * 无
 * 
 * 实验现象
 * 1, 串口打印ESP32S3模组的内部资源。
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

import machine
import esp
import time
import micropython


"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if  __name__ == '__main__':
    
    esp.osdebug(1)                          # 开启原厂 O/S 调试信息
    esp.osdebug(0)                          # 将原厂 O/S 调试信息重定向到 UART(0) 
    freq = machine.freq()                   # 获取CPU当前工作频率
    print(f'当前系统时钟{freq}')             # 打印CPU工作频率
    print(f'内部flash大小{esp.flash_size()/1024/1024}MB') # 打印FLASH大小
    micropython.mem_info()                  # 打印PSRAM信息
    
    while True:
        
        time.sleep_ms(10)                   # 延时10ms

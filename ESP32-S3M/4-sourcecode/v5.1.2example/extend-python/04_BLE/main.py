"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    蓝牙实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习蓝牙控制
 *
 * 硬件资源及引脚分配： 
 * 1,     LED --> ESP32S3 IO
 *        LED --> IO1
 *
 * 实验现象
 * 1, 通过BLUE调试APP来控制LED，当接收“LED ON”命令时，系统打开LED；当接收“LED_OFF”命令时，系统关闭LED。
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
import bluetooth


# 定义全局变量
BLE_MESSAGE = ""

"""
 * @brief       蓝牙类
 * @param       无
 * @retval      无
"""
class ESP32S3_BLE():

    def __init__(self, name):
        # 获取定时器0句柄
        self.timer1 = Timer(0)
        self.name = name
        # 初始化蓝牙
        self.ble = bluetooth.BLE()
        # 开启蓝牙
        self.ble.active(True)
        # 设置蓝牙名称
        self.ble.config(gap_name=name)
        # 配置定时器0且开启定时器
        self.disconnected()
        # 配置蓝牙回调函数
        self.ble.irq(self.ble_irq)
        # 注册蓝牙
        self.register()
        self.advertiser()

    # 蓝牙连接时，点亮LED且关闭定时器0
    def connected(self):
        led.value(1)
        self.timer1.deinit()

    # 蓝牙断开时，闪烁LED
    def disconnected(self):        
        self.timer1.init(period=1000, mode=Timer.PERIODIC, callback=lambda t: led.value(not led.value()))

    # 蓝牙回调函数
    def ble_irq(self, event, data):
        
        global BLE_MESSAGE
        # _IRQ_CENTRAL_CONNECT 蓝牙终端链接了此设备
        if event == 1:
            self.connected()
        # _IRQ_CENTRAL_DISCONNECT 蓝牙终端断开此设备
        elif event == 2:
            self.advertiser()
            self.disconnected()
        # _IRQ_GATTS_WRITE 蓝牙终端向ESP32-S3发送数据，接收数据处理
        elif event == 3:  
            buffer = self.ble.gatts_read(self.rx)
            BLE_MESSAGE = buffer.decode('UTF-8').strip()
            
    def register(self):
        service_uuid = '6E400001-B5A3-F393-E0A9-E50E24DCCA9E'
        reader_uuid = '6E400002-B5A3-F393-E0A9-E50E24DCCA9E'
        sender_uuid = '6E400003-B5A3-F393-E0A9-E50E24DCCA9E'
        services = (
            (
                bluetooth.UUID(service_uuid),
                (
                    (bluetooth.UUID(sender_uuid), bluetooth.FLAG_NOTIFY),
                    (bluetooth.UUID(reader_uuid), bluetooth.FLAG_WRITE),
                )
            ),
        )
        ((self.tx, self.rx,), ) = self.ble.gatts_register_services(services)

    # 向蓝牙APP发送数据
    def send(self, data):
        self.ble.gatts_notify(1, self.tx, data + '\n')

    def advertiser(self):
        name = bytes(self.name, 'UTF-8')
        adv_data = bytearray('\x02\x01\x02', 'UTF-8') + bytearray((len(name) + 1, 0x09), 'UTF-8') + name
        self.ble.gap_advertise(100, adv_data)

"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""
if __name__ == "__main__":
    
    led = Pin(1, Pin.OUT,value = 1)
    # 创建蓝牙对象且设置蓝牙名称
    ble = ESP32S3_BLE("ESP32-S3 BLUE")
    
    while True:
        
        # 打开LED
        if BLE_MESSAGE == 'LED ON':
            led.value(0)
            print('LED is ON.')
            ble.send('LED is ON.')
            BLE_MESSAGE = ""
        # 关闭LED
        elif BLE_MESSAGE == 'LED OFF':
            led.value(1)
            print('LED is OFF.')
            ble.send('LED is OFF.')
            BLE_MESSAGE = ""
        
        time.sleep_ms(100)


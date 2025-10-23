"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    UDP实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：使用SOCKET接口实现UDP实验
 *
 * 硬件资源及引脚分配： 
 * 无
 *
 * 实验现象
 * 1, 连接网络成功之后，我们把网络调试助手设置为UDP协议且填写IP等信息，在发送区填入要发送的数据，
 *    按下“发送”按键向ESP32-S3开发板发送数据，此时开发板把接收到的数据原封不动的发送至网络调试助手。
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

import socket
import network
import time


SSID = "xxx"                    # wifi名称
PASSWORD = "xxx"                # wifi密码
Server_IP = '192.168.101.33'    # 原程IP地址
wlan = None

"""
 * @brief       连接网络
 * @param       无
 * @retval      无
"""
def connect():
    
    global wlan
    # 创建站点接口
    wlan = network.WLAN(network.STA_IF)
    wlan.active(False)
    # 启用站点接口
    wlan.active(True)
    
    # 判断是否连接
    if not wlan.isconnected():
        print('connecting to network...')
        # 连接WiFi
        wlan.connect(SSID, PASSWORD)
        while not wlan.isconnected():
            pass
    # 输出网络信息
    print('network config: ', wlan.ifconfig())

"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""  
if __name__ == '__main__':
    
    # 连接网络
    connect()
    
    while True:
        # 获取本地IP
        ip = wlan.ifconfig()[0]
        print('network config:', ip)
        """
        创建socket 对象，socket.socket(ip 类型，协议)：
        socket.AFINET是ipv4;socket.AFINET6是ipv6
        socket.SOCK_STREAM表示tcp;SOCK_DGRAM表示UDP
        """
        udp_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        # ServerIP+ServerPort
        addr = socket.getaddrinfo('192.168.101.33', 8080)[0][-1]
        print(addr)
        # 发送信息
        udp_socket.sendto("**********************************\r\n",addr)
        udp_socket.sendto(f'正点原子 ESP32-S3 最小系统板 UDP Test\r\n'.encode('utf-8'),addr)
        udp_socket.sendto("**********************************\r\n",addr)
        
        while True:
            try:
                # 每次接收4096字节
                data = udp_socket.recv(4096)
            except :
                udp_socket.close()
                break
            # 回显操作
            udp_socket.sendto(data,addr)


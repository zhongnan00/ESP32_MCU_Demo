"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    TCPClient实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：使用SOCKET接口实现TCPClient实验
 *
 * 硬件资源及引脚分配： 
 * 无
 *
 * 实验现象
 * 1, 连接网络成功之后，我们把网络调试助手设置为TCPServer协议且填写IP等信息，在发送区填入要发送的数据，
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
pos = 0

"""
 * @brief       连接网络
 * @param       无
 * @retval      无
"""
def connect():
    
    global wlan
    wlan = network.WLAN(network.STA_IF)
    wlan.active(False)
    wlan.active(True)
    
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect(SSID, PASSWORD)
        while not wlan.isconnected():
            pass
    print('network config: ', wlan.ifconfig())

"""
 * @brief       模拟goto
 * @param       label:标签
 * @retval      无
"""
def goto(label):

    global pos
    pos = label
    
"""
 * @brief       程序入口
 * @param       无
 * @retval      无
"""  
if __name__ == '__main__':
    
    # 连接网络
    connect()
    
    while True:
        
        while pos == 0:
            # 获取本地IP
            ip = wlan.ifconfig()[0]
            
            """
            创建socket 对象，socket.socket(ip 类型，协议)：
            socket.AFINET是ipv4;socket.AFINET6是ipv6
            socket.SOCK_STREAM表示tcp;SOCK_DGRAM表示UDP
            """
            client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            print('network config:', ip)
            
            """
            和服务器建立连接
            socket对象connect((服务器ip地址，端口号))  类型是元组
            """
            try:
                client_socket.connect((Server_IP,8080))
            except BaseExc1eption:
                client_socket.close()
                print('关闭字节套......')
                goto(0)
                break
            
            print('连接建立成功......')
            # 发送信息
            client_socket.send("**********************************\r\n")
            client_socket.send(f'正点原子 ESP32-S3 最小系统板 TCPClient\r\n'.encode('utf-8'))
            client_socket.send("**********************************\r\n")
            
            while True:
                try:
                    # 每次接收4096字节
                    data = client_socket.recv(4096)
                except BaseExc1eption:
                    client_socket.close()
                    break
                # 如果收到空消息关闭连接
                if (len(data) == 0):
                
                    print("close socket")
                    client_socket.close()
                    break
                
                # 回显操作
                client_socket.send(data)

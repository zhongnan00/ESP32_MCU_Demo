"""
 ******************************************************************************
 * @file     main.py
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    TCPServer实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：使用SOCKET接口实现TCPServer实验
 *
 * 硬件资源及引脚分配： 
 * 无
 *
 * 实验现象
 * 1, 连接网络成功之后，我们把网络调试助手设置为TCPClient协议且填写IP等信息，在发送区填入要发送的数据，
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


SSID = "xxx"          # wifi名称
PASSWORD = "xxx"      # wifi密码
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
            print('network config:', ip)
            """
            创建socket 对象，socket.socket(ip 类型，协议)：
            socket.AFINET是ipv4;socket.AFINET6是ipv6
            socket.SOCK_STREAM表示tcp;SOCK_DGRAM表示UDP
            """
            server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            # 设置端口复用
            server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,True)
            # 绑定本地IP以及端口
            server_socket.bind(('',8080)) # 前面空，绑定服务器的任意一个网卡
            # 监听，参数是同时连接的客户端数量
            server_socket.listen(128)
            # 阻塞等待客户端连接
            # 返回一个元组  （新socket, (客户端IP,端口) ）
            try:
                new_socket, client_ip_port = server_socket.accept()
            except:
                new_socket.close()
                server_socket.close()
                print('关闭字节套......')
                goto(0)
                break
            
            print('连接建立成功......')
            # 发送信息
            new_socket.send("**********************************\r\n")
            new_socket.send(f'正点原子 ESP32-S3 最小系统板 TCPServer\r\n'.encode('utf-8'))
            new_socket.send("**********************************\r\n")
            
            while True:
                try:
                    # 每次接收4096字节
                    data = new_socket.recv(4096)
                except :
                    new_socket.close()
                    server_socket.close()
                    break
                # 如果收到空消息关闭连接
                if (len(data) == 0):
                
                    new_socket.close()
                    server_socket.close()
                    break
                
                # 回显操作
                new_socket.send(data)

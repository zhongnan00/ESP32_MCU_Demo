/**
 ****************************************************************************************************
 * @file        pwm.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       LED PWM 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32-S3 最小系统板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20231201
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __PWM_H
#define __PWM_H

#include "Arduino.h"

/* LED PWM定义 */
#define LED_PWM_PIN       1   /* PWM信号输出的引脚  */
#define LED_PWM_CHANNEL   0   /* LED PWM通道号 */

/* 函数声明 */    
void led_pwm_init(uint16_t frequency, uint8_t resolution);    /* LED PWM初始化函数 */
void pwm_set_duty(uint16_t duty);                             /* PWM占空比设置 */

#endif

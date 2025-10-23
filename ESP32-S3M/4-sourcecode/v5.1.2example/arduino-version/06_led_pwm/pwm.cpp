/**
 ****************************************************************************************************
 * @file        pwm.cpp
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

#include "pwm.h"

/**
 * @brief       LED PWM初始化函数
 * @param       frequency: PWM输出频率，单位HZ
 * @param       resolution: PWM占空比的分辨率1-16，比如设置8，分辨率范围0~255
 * @retval      无
 */
void led_pwm_init(uint16_t frequency, uint8_t resolution)
{
    ledcSetup(LED_PWM_CHANNEL, frequency, resolution);    /* PWM初始化,引脚和通道由pwm.h的LED_PWM_PIN和LED_PWM_CHANNEL宏修改 */
    ledcAttachPin(LED_PWM_PIN, LED_PWM_CHANNEL);          /* 绑定PWM通道到LED_PWM_PIN上 */
}

/**
 * @brief       PWM占空比设置
 * @param       duty: PWM占空比
 * @retval      无
 */
void pwm_set_duty(uint16_t duty)
{
    ledcWrite(LED_PWM_CHANNEL, duty);   /* 改变PWM的占空比,通道由pwm.h的LED_PWM_CHANNEL宏修改 */
}



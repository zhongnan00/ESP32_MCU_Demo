/**
 ****************************************************************************************************
 * @file        exti.cpp
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       EXTI 驱动代码
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

#include "exti.h"
#include "key.h"

uint8_t led_state = 0;        /* 决定灯亮灭状态变量 */

/**
* @brief       初始化外部中断相关IO口
* @param       无
* @retval      无
*/
void exti_init(void) 
{
    key_init();                                                             /* KEY初始化 */
    attachInterrupt(digitalPinToInterrupt(KEY_INT_PIN), key_isr, FALLING);  /* 设置KEY引脚为中断引脚,下降沿触发 */
}

/**
 * @brief      KEY外部中断回调函数
 * @param      无
 * @retval     无
 */
void key_isr(void)
{
    delay(10);
    if (KEY == 0)
    {
        led_state =! led_state;     /* 两种情况：从0变1，从1变为0 */
    }
}

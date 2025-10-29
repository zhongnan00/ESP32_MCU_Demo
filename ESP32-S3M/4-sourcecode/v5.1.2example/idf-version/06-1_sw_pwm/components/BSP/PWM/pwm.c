/**
 ****************************************************************************************************
 * @file        led.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-26
 * @brief       PWM驱动代码
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
 ****************************************************************************************************
 */

#include "pwm.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (4000) // Frequency in Hertz. Set frequency at 4 kHz


/**
 * @brief       初始化PWM
 * @param       resolution： PWM占空比分辨率
 *              freq： PWM信号频率
 * @retval      无
 */
void pwm_init(uint8_t resolution, uint16_t freq)
{
    // ledc_timer_config_t ledc_timer;                 /* LEDC定时器句柄 */
    // ledc_channel_config_t ledc_channel;             /* LEDC通道配置句柄 */

    // /* 配置LEDC定时器 */
    // ledc_timer.duty_resolution = resolution;        /* PWM占空比分辨率 */
    // ledc_timer.freq_hz = freq;                      /* PWM信号频率 */
    // ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;    /* 定时器模式 */
    // ledc_timer.timer_num = LEDC_PWM_TIMER;          /* 定时器序号 */
    // ledc_timer.clk_cfg = LEDC_AUTO_CLK;             /* LEDC时钟源 */
    // ledc_timer_config(&ledc_timer);                 /* 配置定时器 */

    // /* 配置LEDC通道 */
    // ledc_channel.gpio_num = LEDC_PWM_CH0_GPIO;      /* LED控制器通道对应引脚 */
    // ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;  /* LEDC高速模式 */
    // ledc_channel.channel = LEDC_PWM_CH0_CHANNEL;    /* LEDC控制器通道号 */
    // ledc_channel.intr_type = LEDC_INTR_DISABLE;     /* LEDC失能中断 */
    // ledc_channel.timer_sel = LEDC_PWM_TIMER;        /* 定时器序号 */
    // ledc_channel.duty = 0;                          /* 占空比值 */
    // ledc_channel.hpoint = 0;                        /* 占空比起始点 */
    // ledc_channel.flags.output_invert = 0;                  /* 不反转输出 */
    // ledc_channel_config(&ledc_channel);             /* 配置LEDC通道 */
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = resolution,
        .timer_num        = LEDC_PWM_TIMER,
        .freq_hz          = freq,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_PWM_CH0_CHANNEL,
        .timer_sel      = LEDC_PWM_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_PWM_CH0_GPIO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));


    esp_err_t ret = ledc_timer_config(&ledc_timer);
    if (ret != ESP_OK) {
        printf("ledc_timer_config failed: %s\n", esp_err_to_name(ret));
        return;
    }
}

/**
 * @brief       PWM占空比设置
 * @param       duty：PWM占空比
 * @retval      无
 */
void pwm_set_duty(uint16_t duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_PWM_CH0_CHANNEL, duty); /* 设置占空比 */
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_PWM_CH0_CHANNEL);    /* 更新占空比 */
}

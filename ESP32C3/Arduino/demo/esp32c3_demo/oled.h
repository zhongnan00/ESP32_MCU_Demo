/**
 * @file oled.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef OLED_H_
#define OLED_H_

void oled_init(void);   //i2c

void oled_clear(void);

void oled_task_run(void* arg);



#endif /* OLED_H_ */

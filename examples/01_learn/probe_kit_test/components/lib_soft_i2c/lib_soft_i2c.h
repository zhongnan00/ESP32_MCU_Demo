/**
 * @file lib_soft_i2c.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 
#ifndef LIB_SOFT_I2C_H
#define LIB_SOFT_I2C_H

#include <stdint.h>
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"


/**
 * @brief 
 * 
 */
typedef struct {
    gpio_num_t scl_gpio;
    gpio_num_t sda_gpio;
    uint32_t scl_freq;
    i2c_port_t i2c_master_port;    //I2C_NUM_0, I2C_NUM_1

} lib_soft_i2c_cfg_t;



/**
 * @brief 
 * 
 * @param cfg 
 */
void lib_soft_i2c_init(lib_soft_i2c_cfg_t cfg);


/**
 * @brief 
 * 
 */
esp_err_t lib_soft_i2c_deinit(lib_soft_i2c_cfg_t cfg);


esp_err_t lib_soft_i2c_probe(const char *tag, i2c_port_t master_port,uint8_t dev_addr);



esp_err_t lib_soft_i2c_read_bytes(const char *tag, i2c_port_t master_port,
        uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, size_t size);


esp_err_t lib_soft_i2c_write_bytes(const char *tag, i2c_port_t master_port,
        uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, size_t size);


#endif /* LIB_SOFT_I2C_H */
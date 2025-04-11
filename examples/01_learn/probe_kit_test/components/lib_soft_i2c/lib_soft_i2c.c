/**
 * @file lib_soft_i2c.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "lib_soft_i2c.h"
#include "esp_log.h"

static const char *TAG = "LIB_SOFT_I2C";

void lib_soft_i2c_init(lib_soft_i2c_cfg_t cfg)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = cfg.sda_gpio,
        .scl_io_num = cfg.scl_gpio,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = cfg.scl_freq,
    };

ESP_ERROR_CHECK(i2c_param_config(cfg.i2c_master_port, &conf));
ESP_ERROR_CHECK(i2c_driver_install(cfg.i2c_master_port, conf.mode, 0, 0, 0));

}

esp_err_t lib_soft_i2c_deinit(lib_soft_i2c_cfg_t cfg)
{
    if(cfg.i2c_master_port >= I2C_NUM_MAX){
        ESP_LOGE(TAG, "i2c_master_port error");
        return ESP_ERR_INVALID_ARG;
    }
    ESP_ERROR_CHECK(i2c_driver_delete(cfg.i2c_master_port));
    return ESP_OK;
}

/**
 * @brief 
 * 
 * @param tag 
 * @param master_port 
 * @param dev_addr 
 * @return esp_err_t 
 */
esp_err_t lib_soft_i2c_probe(const char *tag, i2c_port_t master_port,uint8_t dev_addr)
{
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    if(!i2c_cmd)
    {   
        ESP_LOGE(tag, "Error i2c_cmd creat fail!");
        return ESP_FAIL;
    }
    ret = i2c_master_start(i2c_cmd);
    if(ret != ESP_OK)
    {
        ESP_LOGE(tag, "Error i2c_master_start fail!");
        i2c_cmd_link_delete(i2c_cmd);
        return ESP_FAIL;
    }

    i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_stop(i2c_cmd);
    i2c_master_cmd_begin(master_port, i2c_cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(i2c_cmd);
    return ESP_OK;
}


/**
 * @brief 
 * 
 * @param tag 
 * @param master_port 
 * @param dev_addr 
 * @param reg_addr 
 * @param data 
 * @param size 
 * @return esp_err_t 
 */
esp_err_t lib_soft_i2c_read_bytes(const char *tag,i2c_port_t master_port,
        uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, size_t size)
{
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    if(!i2c_cmd)
    {
        ESP_LOGE(tag, "Error i2c_cmd creat fail!");
        return ESP_FAIL;
    }
    ret = i2c_master_start(i2c_cmd);
    if(ret != ESP_OK)
    {
        ESP_LOGE(tag, "Error i2c_master_start fail!");
        i2c_cmd_link_delete(i2c_cmd);
        return ESP_FAIL;
    }

    
    i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(i2c_cmd, reg_addr, I2C_MASTER_ACK);

    i2c_master_start(i2c_cmd);
    i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
    for(int i = 0;i < size;i++)
    {
        if(i == size - 1)
            i2c_master_read_byte(i2c_cmd, &data[i], I2C_MASTER_NACK);
        else
            i2c_master_read_byte(i2c_cmd, &data[i], I2C_MASTER_ACK);
    }
    i2c_master_stop(i2c_cmd);
    i2c_master_cmd_begin(master_port, i2c_cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(i2c_cmd);
    return ESP_OK;
}

/**
 * @brief 
 * 
 * @param tag 
 * @param master_port 
 * @param dev_addr 
 * @param reg_addr 
 * @param data 
 * @param size 
 * @return esp_err_t 
 */
esp_err_t lib_soft_i2c_write_bytes(const char *tag, i2c_port_t master_port,
    uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, size_t size)
{
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    if(!i2c_cmd)
    {
        ESP_LOGE(tag, "Error i2c_cmd creat fail!");
        return ESP_FAIL;
    }
    ret = i2c_master_start(i2c_cmd);
    if(ret != ESP_OK)
    {
        ESP_LOGE(tag, "Error i2c_master_start fail!");
        i2c_cmd_link_delete(i2c_cmd);
        return ESP_FAIL;
    }

    i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(i2c_cmd, reg_addr, I2C_MASTER_ACK);
    for(int i = 0;i < size;i++)
    {
        i2c_master_write_byte(i2c_cmd, data[i], I2C_MASTER_ACK);
    }
    i2c_master_stop(i2c_cmd);
    i2c_master_cmd_begin(master_port, i2c_cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(i2c_cmd);
    return ESP_OK;
}
idf_component_register(
                         SRCS "main.c" 
                              "LCD_Driver/Vernon_ST7789T/Vernon_ST7789T.c" 
                              "LCD_Driver/ST7789.c"
                              "LVGL_Driver/LVGL_Driver.c"
                              "LVGL_UI/LVGL_Example.c"
                              "SD_Card/SD_SPI.c"
                              "RGB/RGB.c"
                              "Wireless/Wireless.c"
                              "Wireless/mqtt_app.c" 
                              "Wireless/simple_wifi_sta.c" 
                              "lib_soft_i2c/lib_soft_i2c.c"
                              "sensors/sensor_eeprom.c" 
                              "sensors/sensor_elmos.c" 
                              "sensors/sensor_ntc.c"
                              "common/lib_ring_buffer.c"
                              

                         INCLUDE_DIRS 
                              "./LCD_Driver/Vernon_ST7789T" 
                              "./LCD_Driver" 
                              "./LVGL_Driver" 
                              "./LVGL_UI" 
                              "./SD_Card"
                              "./RGB" 
                              "./Wireless" 
                              "lib_soft_i2c" 
                              "sensors"
                              "common"
                              "."
                       )

idf_component_register(SRCS "sensor_eeprom.c" "sensor_elmos.c" "sensor_ntc.c"
                    INCLUDE_DIRS "." "../lib_soft_i2c"
                    PRIV_REQUIRES driver
                   )

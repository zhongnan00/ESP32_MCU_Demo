#!/bin/bash

# set environment variables

# . $HOME/esp/esp-idf/export.sh

cd /home/liuchao/github/esp-repo/esp-idf
source export.sh

sudo usermod -aG dialout $USER

cd /home/liuchao/github/ESP32_MCU_Demo/ESP32-C6-LCD-1.47-Demo/ESP-IDF/ESP32-C6-LCD-1.47-Test

idf.py set-target esp32c6
# idf.py menuconfig
idf.py build
idf.py -p /dev/ttyACM0 flash monitor

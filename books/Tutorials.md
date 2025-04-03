# ESP32 MCU Demo

##  Environment
```shell
1. Ubuntu 22.04
2. ESP-IDF v4.4
3. Python 3.9.7
4. Visual Studio Code 1.64.2


```

## Guide
```shell
https://docs.espressif.com/projects/esp-idf/zh_CN/v5.4.1/esp32/get-started/index.html


https://docs.espressif.com/projects/esp-idf/zh_CN/v5.4.1/esp32/get-started/linux-macos-setup.html
```

## command
```shell
 2023  cp /home/liuchao/github/esp-repo/esp-idf/examples/get-started/hello_world/* ./
 2024  sudo cp /home/liuchao/github/esp-repo/esp-idf/examples/get-started/hello_world/* ./
 2025  ls
 2026  idf.py set-target esp32c6
 2027  cd 
 2028  cd -
 2029  ls
 2030  cd ..
 2031  ls
 2032  cd ..
 2033  ls
 2034  ls -lh
 2035  cp -r ../esp-repo/esp-idf/examples ./
 2036  cd examples/
 2037  ls
 2038  cd get-started/
 2039  ls
 2040  cd hello_world/
 2041  ls
 2042  idf.py set-target esp32c6
 2043  idf.py menuconfig 
 2044  idf.py build
 2045  idf.py flash
 2046  sudo idf.py flash
 2048  sudo usermod -aG dialout $USER
 2049  newgrp dialout       //solve the permission problem

```


## demo run
```shell

liuchao@liuchao-linux:~/github/ESP32_MCU_Demo/examples/get-started/hello_world$ idf.py -p /dev/ttyACM0 monitor
Executing action: monitor
Running idf_monitor in directory /home/liuchao/github/ESP32_MCU_Demo/examples/get-started/hello_world
Executing "/home/liuchao/.espressif/python_env/idf5.4_py3.10_env/bin/python /home/liuchao/github/esp-repo/esp-idf/tools/idf_monitor.py -p /dev/ttyACM0 -b 115200 --toolchain-prefix riscv32-esp-elf- --target esp32c6 --revision 0 --decode-panic backtrace /home/liuchao/github/ESP32_MCU_Demo/examples/get-started/hello_world/build/hello_world.elf -m '/home/liuchao/.espressif/python_env/idf5.4_py3.10_env/bin/python' '/home/liuchao/github/esp-repo/esp-idf/tools/idf.py' '-p' '/dev/ttyACM0'"...
--- esp-idf-monitor 1.6.0 on /dev/ttyACM0 115200
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
ESP-ROM:esp32c6-20220919
Build:Sep 19 2022
rst:0x15 (USB_UART_HPSYS),boot:0x6f (SPI_FAST_FLASH_BOOT)
Saved PC:0x408039f0
--- 0x408039f0: rv_utils_wait_for_intr at /home/liuchao/github/esp-repo/esp-idf/components/riscv/include/riscv/rv_utils.h:62
---  (inlined by) esp_cpu_wait_for_intr at /home/liuchao/github/esp-repo/esp-idf/components/esp_hw_support/cpu.c:62

SPIWP:0xee
mode:DIO, clock div:2
load:0x40875720,len:0x16b8
load:0x4086c110,len:0xe84
load:0x4086e610,len:0x3058
entry 0x4086c11a
I (23) boot: ESP-IDF v5.4.1 2nd stage bootloader
I (23) boot: compile time Apr  2 2025 17:31:58
I (24) boot: chip revision: v0.1
I (24) boot: efuse block revision: v0.3
I (26) boot.esp32c6: SPI Speed      : 80MHz
I (30) boot.esp32c6: SPI Mode       : DIO
I (34) boot.esp32c6: SPI Flash Size : 4MB
I (38) boot: Enabling RNG early entropy source...
I (42) boot: Partition Table:
I (45) boot: ## Label            Usage          Type ST Offset   Length
I (51) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (58) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (64) boot:  2 factory          factory app      00 00 00010000 00100000
I (71) boot: End of partition table
I (74) esp_image: segment 0: paddr=00010020 vaddr=42018020 size=08b38h ( 35640) map
I (88) esp_image: segment 1: paddr=00018b60 vaddr=40800000 size=074b8h ( 29880) load
I (95) esp_image: segment 2: paddr=00020020 vaddr=42000020 size=1173ch ( 71484) map
I (110) esp_image: segment 3: paddr=00031764 vaddr=408074b8 size=03aa8h ( 15016) load
I (114) esp_image: segment 4: paddr=00035214 vaddr=4080af60 size=01710h (  5904) load
I (118) boot: Loaded app from partition at offset 0x10000
I (119) boot: Disabling RNG early entropy source...
I (135) cpu_start: Unicore app
I (143) cpu_start: Pro cpu start user code
I (143) cpu_start: cpu freq: 160000000 Hz
I (144) app_init: Application information:
I (144) app_init: Project name:     hello_world
I (148) app_init: App version:      d431c0b
I (152) app_init: Compile time:     Apr  2 2025 17:31:52
I (157) app_init: ELF file SHA256:  4f8fbeefb...
I (161) app_init: ESP-IDF:          v5.4.1
I (165) efuse_init: Min chip rev:     v0.0
I (169) efuse_init: Max chip rev:     v0.99 
I (173) efuse_init: Chip rev:         v0.1
I (176) heap_init: Initializing. RAM available for dynamic allocation:
I (183) heap_init: At 4080D5B0 len 0006F060 (444 KiB): RAM
I (188) heap_init: At 4087C610 len 00002F54 (11 KiB): RAM
I (193) heap_init: At 50000000 len 00003FE8 (15 KiB): RTCRAM
I (199) spi_flash: detected chip: generic
I (202) spi_flash: flash io: dio
I (205) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (211) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (218) coexist: coex firmware version: e727207
I (222) coexist: coexist rom version 5b8dcfa
I (227) main_task: Started on CPU0
I (227) main_task: Calling app_main()
Hello world!
This is esp32c6 chip with 1 CPU core(s), WiFi/BLE, 802.15.4 (Zigbee/Thread), silicon revision v0.1, 4MB external flash
Minimum free heap size: 465004 bytes
Restarting in 10 seconds...
Restarting in 9 seconds...
Restarting in 8 seconds...
Restarting in 7 seconds...
Restarting in 6 seconds...
Restarting in 5 seconds...
Restarting in 4 seconds...
Restarting in 3 seconds...
Restarting in 2 seconds...
Restarting in 1 seconds...
Restarting in 0 seconds...
Restarting now.
ESP-ROM:esp32c6-20220919
Build:Sep 19 2022
rst:0xc (SW_CPU),boot:0x6f (SPI_FAST_FLASH_BOOT)
Saved PC:0x4001975a
--- 0x4001975a: software_reset_cpu in ROM
```
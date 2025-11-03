# Readme

## guide
```shell
https://randomnerdtutorials.com/getting-started-with-esp32/#esp32-intro

https://randomnerdtutorials.com/projects-esp32/

```


## log
```shell
Sensor SN: 24T00158
pressure: -1.64 mmHg
pressure: -1.64 mmHg
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.64 mmHg
temp: 28.46 C
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.64 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.64 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.61 mmHg
pressure: -1.62 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.62 mmHg
pressure: -1.61 mmHg
pressure: -1.61 mmHg
pressure: -1.61 mmHg


```



## log
```shell
liuchao@liuchao-linux:~/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp$ idf.py -p /dev/ttyUSB0 flash monitor
Executing action: flash
Running ninja in directory /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build
Executing "ninja flash"...
[1/1] cd /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build/bootloader/esp-idf/e...000 /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build/bootloader/bootloader.bin
Bootloader binary size 0x6f10 bytes. 0xf0 bytes (1%) free.
[6/8] Generating binary image from built executable
esptool.py v4.10.0
Creating esp32 image...
Merged 2 ELF sections
Successfully created esp32 image.
Generated /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build/demo-icp.bin
[7/8] cd /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build/esp-idf/esptool_py &...tition-table.bin /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build/demo-icp.bin
demo-icp.bin binary size 0xe92d0 bytes. Smallest app partition is 0x400000 bytes. 0x316d30 bytes (77%) free.
[7/8] cd /home/liuchao/github/esp-idf/components/esptool_py && /usr/bin/cmake -D IDF_PATH=/home/...M-32E/demo-icp/build -P /home/liuchao/github/esp-idf/components/esptool_py/run_serial_tool.cmake
esptool.py --chip esp32 -p /dev/ttyUSB0 -b 460800 --before=default_reset --after=hard_reset write_flash --flash_mode dio --flash_freq 80m --flash_size detect 0x1000 bootloader/bootloader.bin 0x10000 demo-icp.bin 0x8000 partition_table/partition-table.bin
esptool.py v4.10.0
Serial port /dev/ttyUSB0
Connecting....
Chip is ESP32-D0WD-V3 (revision v3.1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: ec:64:c9:92:3c:3c
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 460800
Changed.
Configuring flash size...
Auto-detected Flash size: 16MB
Flash will be erased from 0x00001000 to 0x00007fff...
Flash will be erased from 0x00010000 to 0x000f9fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Compressed 28432 bytes to 17294...
Writing at 0x00007a4a... (100 %)
Wrote 28432 bytes (17294 compressed) at 0x00001000 in 0.7 seconds (effective 338.4 kbit/s)...
Hash of data verified.
Compressed 955088 bytes to 546490...
Writing at 0x000f6ddb... (100 %)
Wrote 955088 bytes (546490 compressed) at 0x00010000 in 12.4 seconds (effective 614.4 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 129...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (129 compressed) at 0x00008000 in 0.0 seconds (effective 611.0 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
Executing action: monitor
Running idf_monitor in directory /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp
Executing "/home/liuchao/.espressif/python_env/idf5.2_py3.10_env/bin/python /home/liuchao/github/esp-idf/tools/idf_monitor.py -p /dev/ttyUSB0 -b 115200 --toolchain-prefix xtensa-esp32-elf- --target esp32 --revision 0 /home/liuchao/github/ESP32_MCU_Demo/ESP32-WROOM-32E/demo-icp/build/demo-icp.elf -m '/home/liuchao/.espressif/python_env/idf5.2_py3.10_env/bin/python' '/home/liuchao/github/esp-idf/tools/idf.py' '-p' '/dev/ttyUSB0'"...
--- esp-idf-monitor 1.8.0 on /dev/ttyUSB0 115200
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
�����YV��с�ets Jul 29 2019 12:21:46

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0030,len:7524
load:0x40078000,len:16528
ho 0 tail 12 room 4
load:0x40080400,len:4
--- 0x40080400: _init at ??:?
load:0x40080404,len:4312
entry 0x4008065c
I (31) boot: ESP-IDF v5.2.1 2nd stage bootloader
I (31) boot: compile time Oct 31 2025 14:17:04
I (31) boot: Multicore bootloader
I (35) boot: chip revision: v3.1
I (39) qio_mode: Enabling default flash chip QIO
I (44) boot.esp32: SPI Speed      : 80MHz
I (49) boot.esp32: SPI Mode       : QIO
I (54) boot.esp32: SPI Flash Size : 16MB
I (58) boot: Enabling RNG early entropy source...
I (64) boot: Partition Table:
I (67) boot: ## Label            Usage          Type ST Offset   Length
I (75) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (82) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (90) boot:  2 factory          factory app      00 00 00010000 00400000
I (97) boot:  3 vfs              Unknown data     01 81 00500000 00400000
I (104) boot:  4 storage          Unknown data     01 82 00c00000 00400000
I (112) boot: End of partition table
I (116) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=2c248h (180808) map
I (147) esp_image: segment 1: paddr=0003c270 vaddr=3ffbdb60 size=03da8h ( 15784) load
I (149) esp_image: segment 2: paddr=00040020 vaddr=400d0020 size=9dc20h (646176) map
I (230) esp_image: segment 3: paddr=000ddc48 vaddr=3ffc1908 size=00c5ch (  3164) load
I (230) esp_image: segment 4: paddr=000de8ac vaddr=40080000 size=1aa1ch (109084) load
I (267) boot: Loaded app from partition at offset 0x10000
I (267) boot: Disabling RNG early entropy source...
I (279) cpu_start: Multicore app
I (287) cpu_start: Pro cpu start user code
I (287) cpu_start: cpu freq: 160000000 Hz
I (287) cpu_start: Application information:
I (290) cpu_start: Project name:     demo-icp
I (295) cpu_start: App version:      d28d6cf2-dirty
I (301) cpu_start: Compile time:     Oct 31 2025 15:03:51
I (307) cpu_start: ELF file SHA256:  3ece166e4...
I (312) cpu_start: ESP-IDF:          v5.2.1
I (317) cpu_start: Min chip rev:     v0.0
I (322) cpu_start: Max chip rev:     v3.99 
I (327) cpu_start: Chip rev:         v3.1
I (331) heap_init: Initializing. RAM available for dynamic allocation:
I (338) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM
I (345) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM
I (351) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM
I (357) heap_init: At 3FFCA430 len 00015BD0 (86 KiB): DRAM
I (363) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (369) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (376) heap_init: At 4009AA1C len 000055E4 (21 KiB): IRAM
I (383) spi_flash: detected chip: generic
I (387) spi_flash: flash io: qio
W (391) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (401) coexist: coex firmware version: 77cd7f8
I (407) main_task: Started on CPU0
I (411) main_task: Calling app_main()
I (453) BTDM_INIT: BT controller compile version [0f0c5a2]
I (455) BTDM_INIT: Bluetooth MAC: ec:64:c9:92:3c:3e
I (456) phy_init: phy_version 4791,2c4672b,Dec 20 2023,16:06:06
I (1138) SPP_ACCEPTOR_DEMO: ESP_SPP_INIT_EVT
I (1144) SPP_ACCEPTOR_DEMO: ESP_SPP_START_EVT handle:129 sec_id:55 scn:1
I (1147) SPP_ACCEPTOR_DEMO: event: 10
I (1147) SPP_ACCEPTOR_DEMO: Own address:[ec:64:c9:92:3c:3e]
I (1159) sensor_comm: sensor send task has been started!
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158
temp: 28.47 C
W (7205) BT_HCI: hcif conn complete: hdl 0x80, st 0x0
I (7207) SPP_ACCEPTOR_DEMO: event: 16
W (7390) BT_APPL: new conn_srvc id:26, app_id:255
I (7390) SPP_ACCEPTOR_DEMO: ESP_SPP_SRV_OPEN_EVT status:0 handle:129, rem_bda:[04:ea:56:6a:da:23]
I (7439) SPP_ACCEPTOR_DEMO: ESP_SPP_DATA_IND_EVT len:12 handle:129
I (7440) : 48 65 6c 6c 6f 20 45 53 50 33 32 0a 
I (7442) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
Sensor SN: 24T00158
I (7914) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (8941) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (9969) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (10997) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (12025) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (13053) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (14081) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (15110) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (16138) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (17166) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (18195) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (19223) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (20251) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (21280) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (22308) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (23336) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (24365) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (25393) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (26421) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (27450) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (28477) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (29506) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (30535) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (31563) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (32592) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (33621) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (34649) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (35677) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (36706) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (37736) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (38764) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (39792) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (40820) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (41848) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (42877) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (43905) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (44933) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (45961) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (46989) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (48017) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (49045) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (50073) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
Sensor SN: 24T00158
I (51101) SPP_ACCEPTOR_DEMO: ESP_SPP_WRITE_EVT
temp: 28.47 C
W (51617) BT_RFCOMM: port_rfc_closed RFCOMM connection in server:1 state 2 closed: Closed (res: 19)
I (51618) SPP_ACCEPTOR_DEMO: ESP_SPP_CLOSE_EVT status:0 handle:129 close_by_remote:1
W (51709) BT_RFCOMM: rfc_find_lcid_mcb LCID reused LCID:0x40 current:0x0
W (51711) BT_RFCOMM: RFCOMM_DisconnectInd LCID:0x40
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158
temp: 28.47 C
W (53852) BT_HCI: hcif disc complete: hdl 0x80, rsn 0x13
I (53852) SPP_ACCEPTOR_DEMO: event: 17
Sensor SN: 24T00158
temp: 28.47 C
Sensor SN: 24T00158


```
Build:Mar 27 2021
rst:0x1 (POWERON),boot:0xb (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3820,len:0x1918
load:0x403c9700,len:0x4
load:0x403c9704,len:0xe5c
load:0x403cc700,len:0x302c
entry 0x403c993c
I (27) boot: ESP-IDF v5.2.1 2nd stage bootloader
I (27) boot: compile time Oct 24 2025 15:10:14
I (27) boot: Multicore bootloader
I (30) boot: chip revision: v0.2
I (34) qio_mode: Enabling default flash chip QIO
I (39) boot.esp32s3: Boot SPI Speed : 80MHz
I (44) boot.esp32s3: SPI Mode       : QIO
I (48) boot.esp32s3: SPI Flash Size : 16MB
I (53) boot: Enabling RNG early entropy source...
I (59) boot: Partition Table:
I (62) boot: ## Label            Usage          Type ST Offset   Length
I (70) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (77) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (85) boot:  2 factory          factory app      00 00 00010000 001f0000
I (92) boot:  3 vfs              Unknown data     01 81 00200000 00a00000
I (99) boot:  4 storage          Unknown data     01 82 00c00000 00400000
I (107) boot: End of partition table
I (111) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=0d338h ( 54072) map
I (128) esp_image: segment 1: paddr=0001d360 vaddr=3fc93700 size=02cb8h ( 11448) load
I (130) esp_image: segment 2: paddr=00020020 vaddr=42000020 size=1afb8h (110520) map
I (153) esp_image: segment 3: paddr=0003afe0 vaddr=3fc963b8 size=00040h (    64) load
I (154) esp_image: segment 4: paddr=0003b028 vaddr=40374000 size=0f640h ( 63040) load
I (177) boot: Loaded app from partition at offset 0x10000
I (178) boot: Disabling RNG early entropy source...
I (189) cpu_start: Multicore app
I (189) octal_psram: vendor id    : 0x0d (AP)
I (190) octal_psram: dev id       : 0x02 (generation 3)
I (193) octal_psram: density      : 0x03 (64 Mbit)
I (198) octal_psram: good-die     : 0x01 (Pass)
I (203) octal_psram: Latency      : 0x01 (Fixed)
I (208) octal_psram: VCC          : 0x01 (3V)
I (214) octal_psram: SRF          : 0x01 (Fast Refresh)
I (219) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (225) octal_psram: BurstLen     : 0x01 (32 Byte)
I (231) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (237) octal_psram: DriveStrength: 0x00 (1/1)
I (243) MSPI Timing: PSRAM timing tuning index: 5
I (247) esp_psram: Found 8MB PSRAM device
I (252) esp_psram: Speed: 80MHz
I (708) esp_psram: SPI SRAM memory test OK
I (718) cpu_start: Pro cpu start user code
I (718) cpu_start: cpu freq: 240000000 Hz
I (718) cpu_start: Application information:
I (721) cpu_start: Project name:     00_basic
I (726) cpu_start: App version:      3b35eacd-dirty
I (731) cpu_start: Compile time:     Oct 24 2025 15:10:09
I (737) cpu_start: ELF file SHA256:  5ef68161a1fe2d3a...
I (743) cpu_start: ESP-IDF:          v5.2.1
I (748) cpu_start: Min chip rev:     v0.0
I (753) cpu_start: Max chip rev:     v0.99 
I (758) cpu_start: Chip rev:         v0.2
I (762) heap_init: Initializing. RAM available for dynamic allocation:
I (770) heap_init: At 3FC96D60 len 000529B0 (330 KiB): RAM
I (776) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (782) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (788) heap_init: At 600FE010 len 00001FD8 (7 KiB): RTCRAM
I (794) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (802) spi_flash: detected chip: boya
I (806) spi_flash: flash io: qio
I (810) sleep: Configure to isolate all GPIO pins in sleep state
I (817) sleep: Enable automatic switching of GPIO sleep configuration
I (824) main_task: Started on CPU0
I (828) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (837) main_task: Calling app_main()
内核：cup数量2
FLASH size:16 MB flash
PSRAM size: 8388608 bytes
Hello-ESP32
Hello-ESP32
Hello-ESP32
Hello-ESP32
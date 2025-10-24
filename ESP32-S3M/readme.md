# ESP32-S3 

## start process
```shell
1. ROM program start
2. ROM load flash address 0x00 program to RAM
3. flash laod partition table and main program to RAM. include (SRAM, SROM)
4. main start
5. CPU and freeRTOS start , and enter into scheduler

```

## cmd
```shell
 2007  git clone --recursive  https://github.com/espressif/esp-idf.git
 2008  ls
 2009  cd esp-idf/
 2010  ls
 2011  git submodule list
 2012  git submodule status
 2013  git branch
 2014  git fetch --all --tags
 2015  git branch
 2016  git tag
 2017  git checkout v5.1.2
 2018  git status
 2019  git branch
 2020  ls
 2021  history


 2035  idf.py create-component component
 2036  idf.py --list-targets 
 2037  idf.py set-target esp32s3
 2038  pwd
 2039  idf.py clean
 2040  idf.py fullclean 
 2041  history

```
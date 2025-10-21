#!/bin/bash

# set environment variables

# . $HOME/esp/esp-idf/export.sh

cd /home/liuchao/github/esp-repo/esp-idf
source export.sh

sudo usermod -aG dialout $USER

cd -
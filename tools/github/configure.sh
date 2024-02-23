# !/bin/bash

wget -P /opt https://drive.google.com/drive/folders/1GeEZgo0h6MEGzD-4P9WkOIkexywo-e5q?usp=drive_link

cd /opt
#tar xjf gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2
ls
cd -
export PATH="/opt/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH"
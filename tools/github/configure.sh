# !/bin/bash

wget -P /opt https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC
sleep 30

cd /opt
tar -xvjf /opt/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a
cd -

echo "/opt/gcc-arm-none-eabi-10.3-2021.10/bin" >> $GITHUB_PATH

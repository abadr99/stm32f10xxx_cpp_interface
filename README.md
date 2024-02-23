# stm32f10xxx_cpp_interface

## Breif
This repo introduce an interface with stm32 mcu family using C++. for now we are supporting `stm32f103C8T6` mcu. For specific mcu family support contact us.
## How to build?
1) Download Compiler from link: https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC <BR>

    **OR** You can use the following command in terminal
    ```
    wget -P ~/Downloads https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC
    ```
3) Install the compiler by extracting the tar file
    ```
    cd /opt
    tar -xvjf ~/Downloads/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2
    ```
4) Set compiler path to your environment path by adding the following line to ~/.bashrc     file 
    ```
    export PATH="/opt/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH"
    source ~/.bashrc
    ```
5) build the repo 
   ```
   make build 
   ```

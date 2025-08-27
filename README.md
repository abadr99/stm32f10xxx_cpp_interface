# stm32f10xxx_cpp_interface

An object-oriented, lightweight abstraction layer for STM32F10x microcontrollers using modern C++ techniques. This repository enables structured, reusable, and testable embedded development without relying on heavy HAL libraries.

---

## 📌 Project Goals

- Provide a **C++ abstraction layer** for STM32F10x microcontrollers
- Ensure **modularity and readability** using OOP principles
- Enable **unit testing** with **Google Test** (GTest)
- Keep the code **lightweight** and suitable for **resource-constrained systems**

---

## ⚙️ Technologies Used

### 🧠 C++ (Embedded Systems)
- Utilized **C++17** (compatible subset) for abstraction and type safety
- Implemented object-oriented wrappers around microcontroller peripherals
- Avoided dynamic memory and RTTI for safety in embedded contexts

### 🧪 Google Test (GTest)
- Integrated **Google Test** for unit testing peripheral drivers and logic
- Testable code is structured to allow **mocking hardware registers**
- Enabled simulation of peripheral behavior outside the hardware environment

### 🧰 Makefile Toolchain
- Built with `Make` using **GCC ARM Toolchain** (`arm-none-eabi-gcc`)
- Supports compiling, linking, and flashing via `openocd` or `st-flash`
- Organized targets for `build`, `clean`, and `flash` for convenience

### 🧪 Unit Testing on Host
- Unit tests can be compiled and run on the **host machine (x86)** using `g++`
- Hardware register accesses are **mocked** using test doubles/stubs
- GTest suite located in the `tests/` folder

 ### Documentation 
 – Doxygen-ready with full API documentation

 
 ## 🛠️ Development Workflow

This project supports both **embedded builds** (for STM32F10x targets) and **host builds** (for development, testing, and linting).  

---

### 🔨 Compile for Embedded (Firmware)
```bash
# Build firmware for STM32
make

# Flash firmware using ST-Link / OpenOCD
make flash

---

## How to build?
1) Download Compiler from link: https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC <BR>

    **OR** You can use the following command in terminal
    ```
    wget -P ~/Downloads https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC
    ```
2) Install the compiler by extracting the tar file
    ```
    cd ~/Downloads
    tar -xvjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
    cd /opt
    mv ~/Downloads/gcc-arm-none-eabi-10.3-2021.10 .
    ```
3) Set compiler path to your environment path by adding the following line to ~/.bashrc     file 
    ```
    export PATH="/opt/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH"
    source ~/.bashrc
    ```
4) Check if installing compiler is done successfully
   ```
   arm-none-eabi-g++ --help
   ```
6) build the repo 
   ```
   make build 
   ```
## How to upload?
1) Install St-link
   $ sudo apt install stlink-tools

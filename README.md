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

### 🧪 Hardware Validation (STM32 Boards)
- Conducted **real hardware tests** on STM32F10x boards (e.g., STM32F103C8T6 "Blue Pill")
- Verified key peripherals (GPIO, timers, UART) directly on target hardware
- Cross-checked behavior with unit test mocks to ensure consistency
- Ensures the abstraction layer is not only **theoretically testable** but also **practically validated** on STM32 devices

 ### Documentation 
 – Doxygen-ready with full API documentation

 
 ## 🛠️ Development Workflow

This project supports both **embedded builds** (for STM32F10x targets) and **host builds** (for development, testing, and linting).  

---
## Continuous Integration (CI) Workflow
The project uses a CI workflow defined in `ci.yml` that runs on every **pull_request**. This workflow ensures code quality and correctness across different platforms.

### CI Workflow Description:
The workflow is a multi-stage pipeline triggered on `pull_request` and includes the following steps:

1.  **Initial Checks (Parallel)**:
    * `dev-style-checking` 
    * `test-style-checking` 
    * `hardware-tests-style-checking` 
    * `static-analysis` 

2.  **Builds (Parallel, dependent on Initial Checks)**:
    * **Linux Path**: `build-linux` 
    * **Windows Path**: `build-windows` 
    * **RTOS Path**: `build-linux-rtos` 

3.  **Hardware Tests and Unit Tests (Parallel, dependent on Builds)**:
    * **Linux Path**: `build-hardware-tests-linux`  $\rightarrow$ `run-utest-linux` 
    * **Windows Path**: `build-unitests-linux`  $\rightarrow$ `run-utest-windows` 
    * **RTOS Path**: `build-unitests-windows` 

4.  **Hardware Tests (Windows)**:
    * `build-hardware-tests-win...` (2m 4s) (Dependent on `build-windows` and `build-unitests-windows`).

5.  **Final Step**:
    * `code-coverage` (Dependent on all Unit Tests and Hardware Tests succeeding).

---

### 🔨 Compile for Embedded (Firmware)
```bash
# Build firmware for STM32
make

# Flash firmware using ST-Link / OpenOCD
make flash
```
---

## How to build?
1) Download Compiler from link: https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC <BR>

    **OR** You can use the following command in terminal
    ```bash
    wget -P ~/Downloads https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC
    ```
2) Install the compiler by extracting the tar file
    ```bash
    cd ~/Downloads
    tar -xvjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
    cd /opt
    mv ~/Downloads/gcc-arm-none-eabi-10.3-2021.10 .
    ```
3) Set compiler path to your environment path by adding the following line to ~/.bashrc     file 
    ```bash
    export PATH="/opt/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH"
    source ~/.bashrc
    ```
4) Check if installing compiler is done successfully
   ```bash
   arm-none-eabi-g++ --help
   ```
6) build the repo 
   ```bash
   make build 
   ```
## How to upload?
1) Install St-link
```bash
   $ sudo apt install stlink-tools
```

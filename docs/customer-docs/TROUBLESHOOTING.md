# STM32F10xxx C++ Interface Library - Troubleshooting Guide

## 🚨 Common Issues and Solutions

### Build Issues

#### 1. Linker Errors

**Problem:**
```
undefined reference to `stm32::mcal::Gpio::Init()'
undefined reference to `stm32::mcal::Usart::Init()'
```

**Solutions:**
1. **Check library linking:**
   ```makefile
   # Ensure library is linked
   LDFLAGS += -L./stm32f10xxx_cpp_interface/lib -lstm32f10xxx
   ```

2. **Verify library file exists:**
   ```bash
   ls -la stm32f10xxx_cpp_interface/lib/libstm32f10xxx.a
   ```

3. **Check library path:**
   ```makefile
   # Verify path is correct
   STM32_LIB_PATH = -Lstm32f10xxx_cpp_interface/lib
   ```

#### 2. Include Errors

**Problem:**
```
fatal error: mcal/Gpio.h: No such file or directory
fatal error: stm32/mcal/Gpio.h: No such file or directory
```

**Solutions:**
1. **Check include path:**
   ```makefile
   # Add include path
   CXXFLAGS += -Istm32f10xxx_cpp_interface/include
   ```

2. **Verify header files exist:**
   ```bash
   ls -la stm32f10xxx_cpp_interface/include/mcal/
   ```

3. **Check include statement:**
   ```cpp
   // Correct
   #include "mcal/Gpio.h"
   
   // Incorrect
   #include "stm32/mcal/Gpio.h"
   ```

#### 3. Compiler Errors

**Problem:**
```
error: 'stm32' has not been declared
error: 'mcal' is not a namespace-name
```

**Solutions:**
1. **Enable C++17:**
   ```makefile
   CXXFLAGS += -std=c++17
   ```

2. **Check compiler version:**
   ```bash
   arm-none-eabi-g++ --version
   # Should be 10.3-2021.10 or later
   ```

3. **Verify all required headers:**
   ```cpp
   #include "mcal/Gpio.h"
   #include "mcal/Usart.h"
   #include "mcal/Rcc.h"
   ```

#### 4. Build System Issues

**Problem:**
```
make: *** No rule to make target 'stm32f10xxx_cpp_interface/lib/libstm32f10xxx.a'
```

**Solutions:**
1. **Download the correct package:**
   ```bash
   # Download library package, not source package
   wget https://github.com/abadr99/stm32f10xxx_cpp_interface/releases/download/v1.0.0/stm32f10xxx_cpp_interface_v1.0.0-library.tar.gz
   ```

2. **Extract properly:**
   ```bash
   tar -xzf stm32f10xxx_cpp_interface_v1.0.0-library.tar.gz
   ```

3. **Check directory structure:**
   ```
   stm32f10xxx_cpp_interface/
   ├── lib/
   │   └── libstm32f10xxx.a
   ├── include/
   └── docs/
   ```

### Runtime Issues

#### 1. System Not Responding

**Problem:**
- System hangs after initialization
- No response from peripherals
- LED doesn't blink

**Solutions:**
1. **Check clock configuration:**
   ```cpp
   // Ensure proper clock setup
   stm32::mcal::Rcc::Init();
   stm32::mcal::Rcc::SetExternalClock(stm32::mcal::kHseCrystal);
   stm32::mcal::Rcc::InitSysClock();
   ```

2. **Verify peripheral enable sequence:**
   ```cpp
   // Enable peripheral clock before initialization
   stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
   stm32::mcal::Gpio::Init();
   ```

3. **Check initialization order:**
   ```cpp
   // Correct order
   stm32::mcal::Rcc::Init();
   stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
   stm32::mcal::Gpio::Init();
   ```

#### 2. GPIO Issues

**Problem:**
- LED doesn't turn on/off
- Button input not working
- Pin configuration incorrect

**Solutions:**
1. **Check pin configuration:**
   ```cpp
   // Verify pin mode
   stm32::mcal::Gpio::SetPinMode(pin, stm32::mcal::PinMode::kOutputPushPull_10MHz);
   ```

2. **Verify pin numbers:**
   ```cpp
   // Check pin and port definitions
   stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
   ```

3. **Check clock enable:**
   ```cpp
   // Enable GPIO port clock
   stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
   ```

#### 3. USART Issues

**Problem:**
- No serial output
- Garbage characters
- Communication not working

**Solutions:**
1. **Check baud rate:**
   ```cpp
   // Verify baud rate matches terminal
   stm32::mcal::UsartConfig config = {
       // ... other config
       9600  // Match terminal baud rate
   };
   ```

2. **Verify pin configuration:**
   ```cpp
   // Ensure TX/RX pins are configured
   // PA9 - TX, PA10 - RX for USART1
   ```

3. **Check clock enable:**
   ```cpp
   // Enable USART clock
   stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
   ```

#### 4. ADC Issues

**Problem:**
- ADC readings are wrong
- No ADC output
- Conversion not working

**Solutions:**
1. **Check channel configuration:**
   ```cpp
   // Verify channel number
   stm32::mcal::AdcConfig config = {
       stm32::mcal::kADC1,
       stm32::mcal::kRight,
       stm32::mcal::kChannel0,  // Check channel
       // ... other config
   };
   ```

2. **Verify sampling time:**
   ```cpp
   // Increase sampling time if needed
   stm32::mcal::kCycles_239_5  // Longer sampling time
   ```

3. **Check clock enable:**
   ```cpp
   // Enable ADC clock
   stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kADC1);
   ```

### Performance Issues

#### 1. Slow Execution

**Problem:**
- System runs slowly
- Delays are too long
- Poor responsiveness

**Solutions:**
1. **Optimize compiler flags:**
   ```makefile
   CXXFLAGS += -O3 -mcpu=cortex-m3 -mthumb
   ```

2. **Check clock frequency:**
   ```cpp
   // Ensure system clock is set correctly
   stm32::mcal::Rcc::InitSysClock();
   ```

3. **Minimize function calls in loops:**
   ```cpp
   // Avoid repeated function calls
   for (int i = 0; i < 1000; i++) {
       // Bad: repeated function call
       // Good: store result once
   }
   ```

#### 2. Memory Issues

**Problem:**
- Stack overflow
- Heap fragmentation
- Out of memory

**Solutions:**
1. **Use static allocation:**
   ```cpp
   // Good: static allocation
   static stm32::mcal::Usart usart(config);
   
   // Bad: dynamic allocation
   // stm32::mcal::Usart* usart = new stm32::mcal::Usart(config);
   ```

2. **Optimize memory usage:**
   ```makefile
   # Enable dead code elimination
   CXXFLAGS += -ffunction-sections -fdata-sections
   LDFLAGS += -Wl,--gc-sections
   ```

3. **Check stack size:**
   ```ld
   /* In linker script */
   _Min_Stack_Size = 0x400;  /* 1KB stack */
   ```

### Hardware Issues

#### 1. MCU Not Responding

**Problem:**
- No response from MCU
- Programmer can't connect
- Bootloader issues

**Solutions:**
1. **Check connections:**
   - Verify ST-Link connections
   - Check power supply
   - Ensure proper grounding

2. **Reset MCU:**
   ```bash
   # Reset using ST-Link
   st-flash reset
   ```

3. **Check boot pins:**
   - BOOT0 = 0 (normal boot)
   - BOOT1 = 0

#### 2. Peripheral Not Working

**Problem:**
- Specific peripheral not responding
- Hardware malfunction
- Configuration issues

**Solutions:**
1. **Check hardware connections:**
   - Verify pin connections
   - Check power supply
   - Ensure proper signal levels

2. **Test with simple code:**
   ```cpp
   // Minimal test code
   stm32::mcal::Gpio::Init();
   stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
   stm32::mcal::Gpio::SetPinMode(led, stm32::mcal::PinMode::kOutputPushPull_10MHz);
   stm32::mcal::Gpio::SetPinValue(led, stm32::mcal::DigitalVoltage::kHigh);
   ```

3. **Check datasheet:**
   - Verify pin functions
   - Check electrical characteristics
   - Review timing requirements

## 🔍 Debugging Techniques

### 1. LED Debugging

**Use LED to indicate system status:**
```cpp
// System alive indicator
stm32::mcal::Pin status_led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
stm32::mcal::Gpio::SetPinMode(status_led, stm32::mcal::PinMode::kOutputPushPull_10MHz);

// Toggle LED to show system is running
while (1) {
    stm32::mcal::Gpio::TogglePinValue(status_led);
    for (volatile int i = 0; i < 1000000; i++);
}
```

### 2. USART Debugging

**Send debug messages via USART:**
```cpp
void DebugPrint(const char* message) {
    for (int i = 0; message[i] != '\0'; i++) {
        usart.Transmit(message[i]);
    }
    usart.Transmit('\r');
    usart.Transmit('\n');
}

// Usage
DebugPrint("System initialized");
DebugPrint("ADC reading: 1234");
```

### 3. Breakpoint Debugging

**Use GDB with OpenOCD:**
```bash
# Start OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg

# Start GDB
arm-none-eabi-gdb your_program.elf
(gdb) target remote localhost:3333
(gdb) break main
(gdb) continue
```

### 4. Memory Inspection

**Check memory usage:**
```cpp
// Check stack usage
extern uint32_t _estack;
extern uint32_t _Min_Stack_Size;
uint32_t stack_usage = (uint32_t)&_estack - (uint32_t)__get_MSP();

// Check heap usage
extern uint32_t _Min_Heap_Size;
uint32_t heap_usage = (uint32_t)sbrk(0) - (uint32_t)&_end;
```

## 📋 Debug Checklist

### Before Reporting Issues

1. **Check basic setup:**
   - [ ] MCU is powered
   - [ ] ST-Link connected properly
   - [ ] Boot pins configured correctly
   - [ ] Clock configuration is correct

2. **Verify code:**
   - [ ] All required headers included
   - [ ] Library linked properly
   - [ ] Compiler flags correct
   - [ ] Initialization sequence correct

3. **Test hardware:**
   - [ ] Simple GPIO test works
   - [ ] USART output visible
   - [ ] ADC readings reasonable
   - [ ] No hardware faults

4. **Check documentation:**
   - [ ] API reference consulted
   - [ ] Examples reviewed
   - [ ] Troubleshooting guide checked

## 📞 Getting Help

### Self-Help Resources

1. **Documentation:**
   - [API Reference](API_REFERENCE.md)
   - [Examples](EXAMPLES.md)
   - [Customer Guide](CUSTOMER_GUIDE.md)

2. **Online Resources:**
   - STM32F10x Reference Manual
   - STM32F10x Programming Manual
   - ARM Cortex-M3 Technical Reference Manual

### Reporting Issues

When reporting issues, please include:

1. **System Information:**
   - MCU model and version
   - Compiler version and flags
   - Library version
   - Operating system

2. **Problem Description:**
   - What you're trying to do
   - What happens vs. what you expect
   - Error messages (complete)
   - Steps to reproduce

3. **Code and Configuration:**
   - Minimal code example
   - Makefile/build configuration
   - Hardware connections
   - Clock configuration

4. **Debugging Information:**
   - What you've already tried
   - Debug output (if any)
   - Hardware test results
   - Related documentation checked

### Contact Information

- **GitHub Issues**: [Create an issue](https://github.com/abadr99/stm32f10xxx_cpp_interface/issues)
- **GitHub Discussions**: [Community discussions](https://github.com/abadr99/stm32f10xxx_cpp_interface/discussions)
- **Documentation**: Check the [docs/](docs/) folder

## 🔧 Advanced Troubleshooting

### 1. Timing Issues

**Problem:**
- Timing-sensitive operations fail
- Interrupts not firing on time
- PWM output incorrect

**Solutions:**
1. **Check system clock:**
   ```cpp
   // Verify clock frequency
   uint32_t sysclk = stm32::mcal::Rcc::GetSystemClockFreq();
   // Should be 72MHz for STM32F103
   ```

2. **Optimize interrupt priorities:**
   ```cpp
   // Set appropriate interrupt priorities
   stm32::mcal::Nvic::SetPriority(IRQn, priority);
   ```

3. **Use hardware timers:**
   ```cpp
   // Use hardware timers for precise timing
   stm32::mcal::Timer timer(stm32::mcal::kTIM2);
   ```

### 2. Power Issues

**Problem:**
- System resets unexpectedly
- Peripheral behavior erratic
- Power consumption high

**Solutions:**
1. **Check power supply:**
   - Verify 3.3V supply is stable
   - Check current capacity
   - Ensure proper decoupling

2. **Optimize power usage:**
   ```cpp
   // Disable unused peripherals
   stm32::mcal::Rcc::Disable(stm32::mcal::Peripheral::kUnusedPeripheral);
   ```

3. **Use sleep modes:**
   ```cpp
   // Enter sleep mode when idle
   __WFI();  // Wait for interrupt
   ```

### 3. EMI Issues

**Problem:**
- System affected by external interference
- Communication errors
- Unstable operation

**Solutions:**
1. **Hardware design:**
   - Proper PCB layout
   - Good grounding
   - Shielding if needed

2. **Software filtering:**
   ```cpp
   // Filter noisy inputs
   uint16_t filtered_value = (old_value + new_value) / 2;
   ```

3. **Error detection:**
   ```cpp
   // Check for communication errors
   if (usart.IsError()) {
       // Handle error
   }
   ```

## 📊 Performance Monitoring

### 1. Execution Time Measurement

```cpp
// Measure function execution time
uint32_t start_time = stm32::mcal::SysTick::GetTick();
// ... function to measure ...
uint32_t end_time = stm32::mcal::SysTick::GetTick();
uint32_t execution_time = end_time - start_time;
```

### 2. Memory Usage Monitoring

```cpp
// Monitor stack usage
uint32_t stack_usage = (uint32_t)&_estack - (uint32_t)__get_MSP();
if (stack_usage > 0x300) {  // 768 bytes
    // Stack usage is high
}
```

### 3. Peripheral Status Monitoring

```cpp
// Check peripheral status
if (usart.IsError()) {
    // Handle USART error
}
if (dma.IsTransferComplete()) {
    // Process completed transfer
}
```

---

**Remember: Most issues can be resolved by checking the basics first - power, connections, and proper initialization sequence.**

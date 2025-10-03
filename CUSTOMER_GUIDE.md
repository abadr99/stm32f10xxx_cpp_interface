# STM32F10xxx C++ Interface Library - Customer Guide

## 🎯 Overview

This guide explains how to use the STM32F10xxx C++ Interface Library in your embedded projects. The library provides a lightweight, object-oriented C++ abstraction layer for STM32F10x microcontrollers.

## 📦 Getting Started

### Option 1: Use Pre-built Library (Recommended)

#### 1. Download the Latest Release
1. Go to the [Releases page](https://github.com/abadr99/stm32f10xxx_cpp_interface/releases)
2. Download `stm32f10xxx_cpp_interface_vX.X.X-library.tar.gz`
3. Extract to your project directory:
   ```bash
   tar -xzf stm32f10xxx_cpp_interface_v1.0.0-library.tar.gz
   ```

#### 2. Project Structure
Your project should look like this:
```
your-project/
├── src/
│   └── main.cpp
├── include/
├── stm32f10xxx_cpp_interface/
│   ├── lib/
│   │   └── libstm32f10xxx.a
│   ├── include/
│   │   ├── mcal/
│   │   ├── hal/
│   │   └── utils/
│   ├── docs/
│   ├── examples/
│   ├── README.md
│   └── INTEGRATION_GUIDE.md
└── Makefile
```

#### 3. Configure Your Build System

**Makefile Configuration:**
```makefile
# STM32 Library paths
STM32_INC_PATH = -Istm32f10xxx_cpp_interface/include
STM32_LIB_PATH = -Lstm32f10xxx_cpp_interface/lib
STM32_LIBS = -lstm32f10xxx

# Compiler flags
CXXFLAGS += $(STM32_INC_PATH) -std=c++17 -O3 -mcpu=cortex-m3 -mthumb

# Linker flags
LDFLAGS += $(STM32_LIB_PATH) $(STM32_LIBS)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
```

**CMake Configuration:**
```cmake
# Add include directory
include_directories(stm32f10xxx_cpp_interface/include)

# Link the library
target_link_libraries(your_target stm32f10xxx_cpp_interface/lib/libstm32f10xxx.a)
```

### Option 2: Use Source Code

#### 1. Download Source Package
1. Download `stm32f10xxx_cpp_interface_vX.X.X-source.tar.gz`
2. Extract to your project directory:
   ```bash
   tar -xzf stm32f10xxx_cpp_interface_v1.0.0-source.tar.gz
   ```

#### 2. Build with Source
```makefile
# STM32 Library source files
STM32_SOURCES = $(wildcard stm32f10xxx_cpp_interface/dev/src/mcal/*.cpp)
STM32_INCLUDES = -Istm32f10xxx_cpp_interface/dev/inc

# Compiler flags
CXXFLAGS += $(STM32_INCLUDES) -std=c++17 -O3 -mcpu=cortex-m3 -mthumb

# Build target
$(TARGET): $(OBJECTS) $(STM32_SOURCES)
	$(CXX) $(OBJECTS) $(STM32_SOURCES) -o $@ $(LDFLAGS)
```

## 🚀 Basic Usage Example

### Simple GPIO and USART Example
```cpp
// main.cpp
#include "mcal/Gpio.h"
#include "mcal/Usart.h"
#include "mcal/Rcc.h"

int main() {
    // Initialize system clock
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::SetExternalClock(stm32::mcal::kHseCrystal);
    stm32::mcal::Rcc::InitSysClock();
    
    // Enable peripherals
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure LED pin (PC13)
    stm32::mcal::Pin led_pin(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
    stm32::mcal::Gpio::SetPinMode(led_pin, stm32::mcal::PinMode::kOutputPushPull_10MHz);
    
    // Configure USART
    stm32::mcal::UsartConfig usart_config = {
        stm32::mcal::kUsart1,
        stm32::mcal::kRxTx,
        stm32::mcal::kSb_1_,
        stm32::mcal::kDataBits_8_,
        stm32::mcal::kNo_Parity,
        stm32::mcal::kNone,
        9600
    };
    
    stm32::mcal::Usart usart(usart_config);
    usart.Init();
    
    // Main loop
    while (1) {
        // Toggle LED
        stm32::mcal::Gpio::TogglePinValue(led_pin);
        
        // Send message via USART
        usart.Transmit('H');
        usart.Transmit('e');
        usart.Transmit('l');
        usart.Transmit('l');
        usart.Transmit('o');
        usart.Transmit('\n');
        
        // Simple delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

## 🔧 Supported Peripherals

### MCAL (Microcontroller Abstraction Layer)
- **GPIO**: Pin configuration and control
- **USART**: Serial communication (UART)
- **SPI**: SPI communication interface
- **I2C**: I2C communication interface
- **ADC**: Analog-to-digital conversion
- **DMA**: Direct memory access
- **RCC**: Clock configuration
- **NVIC**: Interrupt control
- **EXTI**: External interrupt handling
- **RTC**: Real-time clock

### HAL (Hardware Abstraction Layer)
- **Timer**: Timer functionality
- **CAN**: CAN bus communication
- **Flash**: Flash memory operations

## 📚 Documentation

### Available Documentation
- **API Reference**: Complete API documentation in `docs/` folder
- **Integration Guide**: Detailed integration instructions in `INTEGRATION_GUIDE.md`
- **Examples**: Example projects in `examples/` folder
- **README**: Package overview and quick start

### Viewing Documentation
1. Open `docs/index.html` in a web browser
2. Navigate through the API reference
3. Check examples for usage patterns

## 🛠️ Configuration Examples

### Clock Configuration
```cpp
// Set system clock to 72MHz
stm32::mcal::Rcc::SetExternalClock(stm32::mcal::kHseCrystal);
stm32::mcal::Rcc::InitSysClock();
```

### GPIO Configuration
```cpp
// Configure pin as output
stm32::mcal::Pin pin(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
stm32::mcal::Gpio::SetPinMode(pin, stm32::mcal::PinMode::kOutputPushPull_10MHz);

// Configure pin as input with pull-up
stm32::mcal::Pin button(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin0);
stm32::mcal::Gpio::SetPinMode(button, stm32::mcal::PinMode::kInputPullUp);
```

### USART Configuration
```cpp
// Configure USART for 115200 baud
stm32::mcal::UsartConfig config = {
    stm32::mcal::kUsart1,
    stm32::mcal::kRxTx,
    stm32::mcal::kSb_1_,
    stm32::mcal::kDataBits_8_,
    stm32::mcal::kNo_Parity,
    stm32::mcal::kNone,
    115200
};

stm32::mcal::Usart usart(config);
usart.Init();
```

### ADC Configuration
```cpp
// Configure ADC
stm32::mcal::AdcConfig adc_config = {
    stm32::mcal::kADC1,
    stm32::mcal::kRight,
    stm32::mcal::kChannel0,
    stm32::mcal::kRegular,
    stm32::mcal::kSingle,
    stm32::mcal::kSoftware,
    stm32::mcal::kCycles_239_5
};

stm32::mcal::ADC adc(adc_config);
adc.Init();
```

## 🔍 Error Handling

The library provides basic error handling through return values:
```cpp
// Check if operation was successful
if (usart.Init()) {
    // USART initialized successfully
    usart.Transmit('A');
} else {
    // Handle initialization error
    // LED indication or error logging
}
```

## 💾 Memory Requirements

### Library Footprint
- **Flash**: ~15KB (library code)
- **RAM**: ~2KB (library data)
- **Stack**: Minimum 1KB recommended

### Memory Usage Tips
- Use `-Os` optimization for size
- Enable `-ffunction-sections` and `-fdata-sections`
- Use `-Wl,--gc-sections` to remove unused code

## 🔧 Compiler Requirements

### Required Tools
- **ARM GCC**: 10.3-2021.10 or later
- **C++ Standard**: C++17 or later
- **Target**: ARM Cortex-M3 (STM32F10x)

### Compiler Flags
```makefile
CXXFLAGS = -std=c++17 -O3 -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections
LDFLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections
```

## 🎯 Supported MCUs

### Tested MCUs
- **STM32F103C8T6** (Blue Pill) - 64KB Flash, 20KB RAM
- **STM32F103RBT6** - 128KB Flash, 20KB RAM
- **STM32F103VCT6** - 256KB Flash, 48KB RAM

### Compatible MCUs
- All STM32F10x variants
- STM32F101 series
- STM32F102 series
- STM32F103 series

## 🚨 Troubleshooting

### Common Issues

#### 1. Linker Errors
```
undefined reference to `stm32::mcal::Gpio::Init()'
```
**Solution:**
- Ensure library path is correct in LDFLAGS
- Check that library file exists
- Verify library is linked: `-lstm32f10xxx`

#### 2. Include Errors
```
fatal error: mcal/Gpio.h: No such file or directory
```
**Solution:**
- Verify include path in CXXFLAGS
- Check header file locations
- Ensure `-Istm32f10xxx_cpp_interface/include` is set

#### 3. Build Errors
```
error: 'stm32' has not been declared
```
**Solution:**
- Ensure C++17 standard is enabled: `-std=c++17`
- Check compiler version compatibility
- Verify all required headers are included

#### 4. Runtime Issues
```
System not responding after initialization
```
**Solution:**
- Check clock configuration
- Verify peripheral enable sequence
- Ensure proper initialization order

### Debug Tips
1. **Enable Debug Output**: Use USART for debugging
2. **Check Clock Settings**: Verify system clock frequency
3. **Validate Pin Configuration**: Ensure correct pin modes
4. **Monitor Memory Usage**: Check stack and heap usage

## 📞 Support

### Getting Help
1. **Check Documentation**: Review `docs/` folder and `INTEGRATION_GUIDE.md`
2. **Review Examples**: Look at `examples/` folder for usage patterns
3. **GitHub Issues**: Create an issue on the repository
4. **Community**: Check project discussions and forums

### Reporting Issues
When reporting issues, please include:
- MCU model and version
- Compiler version and flags
- Complete error messages
- Minimal code example
- Expected vs actual behavior

## 🔄 Version Management

### Checking Version
The library version is available in the release package:
```bash
# Check release version
cat stm32f10xxx_cpp_interface/README.md | grep "Version"
```

### Upgrading
1. Download the latest release
2. Replace the library files
3. Check the changelog for breaking changes
4. Update your code if necessary
5. Test thoroughly

### Version Compatibility
- **Major versions**: May include breaking changes
- **Minor versions**: Add features, backward compatible
- **Patch versions**: Bug fixes, backward compatible

## 📋 Best Practices

### Code Organization
1. **Separate Concerns**: Keep hardware abstraction separate from application logic
2. **Use Namespaces**: Leverage `stm32::mcal` namespace for clarity
3. **Error Handling**: Always check return values
4. **Resource Management**: Properly initialize and cleanup peripherals

### Performance
1. **Optimize Compiler Flags**: Use appropriate optimization levels
2. **Minimize Interrupts**: Keep ISRs short and efficient
3. **Memory Management**: Avoid dynamic allocation
4. **Clock Configuration**: Use appropriate clock frequencies

### Testing
1. **Unit Testing**: Test individual components
2. **Integration Testing**: Test complete system
3. **Hardware Testing**: Validate on actual hardware
4. **Performance Testing**: Measure timing and memory usage

## 🎉 Conclusion

The STM32F10xxx C++ Interface Library provides a modern, efficient way to develop embedded applications for STM32F10x microcontrollers. With its object-oriented design, comprehensive documentation, and extensive examples, you can quickly integrate it into your projects and focus on your application logic rather than low-level hardware details.

For the latest updates, documentation, and examples, visit the [GitHub repository](https://github.com/abadr99/stm32f10xxx_cpp_interface).

---

**Happy coding with STM32F10xxx C++ Interface Library! 🚀**

# STM32F10xxx C++ Interface Library - API Reference

## 📚 Overview

This document provides detailed API reference for the STM32F10xxx C++ Interface Library. All classes and functions are organized by module for easy navigation.

## 🏗️ Architecture

The library follows a layered architecture:

```
Application Layer
       ↓
   HAL Layer (Hardware Abstraction Layer)
       ↓
   MCAL Layer (Microcontroller Abstraction Layer)
       ↓
   STM32 Hardware
```

## 📦 Namespaces

### `stm32::mcal`
Microcontroller Abstraction Layer - Direct hardware register access and peripheral control.

### `stm32::hal`
Hardware Abstraction Layer - Higher-level device drivers and abstractions.

### `stm32::utils`
Utility functions and helper classes.

## 🔧 MCAL (Microcontroller Abstraction Layer)

### GPIO (General Purpose Input/Output)

#### Classes
- **`Gpio`**: Static class for GPIO operations

#### Functions
```cpp
// Initialize GPIO subsystem
static void Init();

// Set pin mode
static void SetPinMode(const Pin& pin, PinMode mode);

// Set pin value
static void SetPinValue(const Pin& pin, DigitalVoltage value);

// Get pin value
static DigitalVoltage GetPinValue(const Pin& pin);

// Toggle pin value
static void TogglePinValue(const Pin& pin);
```

#### Enums
```cpp
enum class Port {
    kPortA = 0,
    kPortB = 1,
    kPortC = 2,
    kPortD = 3,
    kPortE = 4,
    kPortF = 5,
    kPortG = 6
};

enum class Pin {
    kPin0 = 0, kPin1 = 1, kPin2 = 2, kPin3 = 3,
    kPin4 = 4, kPin5 = 5, kPin6 = 6, kPin7 = 7,
    kPin8 = 8, kPin9 = 9, kPin10 = 10, kPin11 = 11,
    kPin12 = 12, kPin13 = 13, kPin14 = 14, kPin15 = 15
};

enum class PinMode {
    kInputAnalog = 0,
    kInputFloating = 1,
    kInputPullUp = 2,
    kInputPullDown = 3,
    kOutputPushPull_10MHz = 4,
    kOutputOpenDrain_10MHz = 5,
    kOutputPushPull_2MHz = 6,
    kOutputOpenDrain_2MHz = 7,
    kOutputPushPull_50MHz = 8,
    kOutputOpenDrain_50MHz = 9
};

enum class DigitalVoltage {
    kLow = 0,
    kHigh = 1
};
```

#### Example
```cpp
#include "mcal/Gpio.h"

// Configure LED pin
stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
stm32::mcal::Gpio::SetPinMode(led, stm32::mcal::PinMode::kOutputPushPull_10MHz);
stm32::mcal::Gpio::SetPinValue(led, stm32::mcal::DigitalVoltage::kHigh);
```

### USART (Universal Synchronous Asynchronous Receiver Transmitter)

#### Classes
- **`Usart`**: USART peripheral control

#### Constructor
```cpp
Usart(const UsartConfig& config);
```

#### Functions
```cpp
// Initialize USART
bool Init();

// Transmit single byte
void Transmit(uint8_t data);

// Receive single byte
uint8_t Receive();

// Check if data is ready
bool IsDataReady();

// Set baud rate
void SetBaudRate(uint32_t baud_rate);
```

#### Configuration Structure
```cpp
struct UsartConfig {
    UsartInstance instance;
    UsartMode mode;
    StopBits stop_bits;
    DataBits data_bits;
    Parity parity;
    FlowControl flow_control;
    uint32_t baud_rate;
};
```

#### Enums
```cpp
enum class UsartInstance {
    kUsart1 = 0,
    kUsart2 = 1,
    kUsart3 = 2
};

enum class UsartMode {
    kRxOnly = 0,
    kTxOnly = 1,
    kRxTx = 2
};

enum class StopBits {
    kSb_1_ = 0,
    kSb_0_5 = 1,
    kSb_2 = 2,
    kSb_1_5 = 3
};

enum class DataBits {
    kDataBits_8_ = 0,
    kDataBits_9 = 1
};

enum class Parity {
    kNo_Parity = 0,
    kEven_Parity = 1,
    kOdd_Parity = 2
};

enum class FlowControl {
    kNone = 0,
    kRts = 1,
    kCts = 2,
    kRtsCts = 3
};
```

#### Example
```cpp
#include "mcal/Usart.h"

// Configure USART
stm32::mcal::UsartConfig config = {
    stm32::mcal::kUsart1,
    stm32::mcal::kRxTx,
    stm32::mcal::kSb_1_,
    stm32::mcal::kDataBits_8_,
    stm32::mcal::kNo_Parity,
    stm32::mcal::kNone,
    9600
};

stm32::mcal::Usart usart(config);
usart.Init();
usart.Transmit('A');
```

### RCC (Reset and Clock Control)

#### Classes
- **`Rcc`**: Static class for clock management

#### Functions
```cpp
// Initialize RCC
static void Init();

// Set external clock source
static void SetExternalClock(HseType hse_type);

// Initialize system clock
static void InitSysClock();

// Enable peripheral clock
static void Enable(Peripheral peripheral);

// Disable peripheral clock
static void Disable(Peripheral peripheral);

// Get system clock frequency
static uint32_t GetSystemClockFreq();
```

#### Enums
```cpp
enum class HseType {
    kHseCrystal = 0,
    kHseRc = 1
};

enum class Peripheral {
    kIOPA = 0, kIOPB = 1, kIOPC = 2, kIOPD = 3,
    kIOPE = 4, kIOPF = 5, kIOPG = 6,
    kUSART1 = 7, kUSART2 = 8, kUSART3 = 9,
    kSPI1 = 10, kSPI2 = 11, kSPI3 = 12,
    kI2C1 = 13, kI2C2 = 14,
    kADC1 = 15, kADC2 = 16, kADC3 = 17,
    kDMA1 = 18, kDMA2 = 19,
    kTIM1 = 20, kTIM2 = 21, kTIM3 = 22, kTIM4 = 23,
    kCAN1 = 24, kCAN2 = 25,
    kRTC = 26, kBKP = 27, kPWR = 28
};
```

#### Example
```cpp
#include "mcal/Rcc.h"

// Initialize clock system
stm32::mcal::Rcc::Init();
stm32::mcal::Rcc::SetExternalClock(stm32::mcal::kHseCrystal);
stm32::mcal::Rcc::InitSysClock();

// Enable peripherals
stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
```

### ADC (Analog-to-Digital Converter)

#### Classes
- **`ADC`**: ADC peripheral control

#### Constructor
```cpp
ADC(const AdcConfig& config);
```

#### Functions
```cpp
// Initialize ADC
bool Init();

// Start single conversion
bool StartSingleConversion();

// Get conversion result
uint16_t GetConversionResult();

// Get temperature value
float GetTemperatureValue();
```

#### Configuration Structure
```cpp
struct AdcConfig {
    AdcInstance instance;
    Alignment alignment;
    AdcChannel channel;
    ConversionMode mode;
    TriggerSource trigger;
    SamplingTime sampling_time;
};
```

#### Enums
```cpp
enum class AdcInstance {
    kADC1 = 0,
    kADC2 = 1,
    kADC3 = 2
};

enum class Alignment {
    kRight = 0,
    kLeft = 1
};

enum class AdcChannel {
    kChannel0 = 0, kChannel1 = 1, kChannel2 = 2, kChannel3 = 3,
    kChannel4 = 4, kChannel5 = 5, kChannel6 = 6, kChannel7 = 7,
    kChannel8 = 8, kChannel9 = 9, kChannel10 = 10, kChannel11 = 11,
    kChannel12 = 12, kChannel13 = 13, kChannel14 = 14, kChannel15 = 15,
    kChannel16 = 16, kChannel17 = 17
};

enum class ConversionMode {
    kSingle = 0,
    kContinuous = 1,
    kScan = 2,
    kDiscontinuous = 3
};

enum class TriggerSource {
    kSoftware = 0,
    kTimer1 = 1,
    kTimer2 = 2,
    kTimer3 = 3,
    kExti11 = 4
};

enum class SamplingTime {
    kCycles_1_5 = 0,
    kCycles_7_5 = 1,
    kCycles_13_5 = 2,
    kCycles_28_5 = 3,
    kCycles_41_5 = 4,
    kCycles_55_5 = 5,
    kCycles_71_5 = 6,
    kCycles_239_5 = 7
};
```

#### Example
```cpp
#include "mcal/Adc.h"

// Configure ADC
stm32::mcal::AdcConfig config = {
    stm32::mcal::kADC1,
    stm32::mcal::kRight,
    stm32::mcal::kChannel0,
    stm32::mcal::kSingle,
    stm32::mcal::kSoftware,
    stm32::mcal::kCycles_239_5
};

stm32::mcal::ADC adc(config);
adc.Init();
adc.StartSingleConversion();
uint16_t result = adc.GetConversionResult();
```

### DMA (Direct Memory Access)

#### Classes
- **`DMA`**: DMA peripheral control

#### Constructor
```cpp
DMA(const DmaConfig& config);
```

#### Functions
```cpp
// Initialize DMA
bool Init();

// Enable DMA
void Enable();

// Disable DMA
void Disable();

// Check if transfer is complete
bool IsTransferComplete();

// Get transfer status
DmaStatus GetStatus();
```

#### Configuration Structure
```cpp
struct DmaConfig {
    DmaChannel channel;
    DmaDirection direction;
    uint32_t sourceBaseAddr;
    uint32_t destinationBaseAddr;
    uint32_t bufferSize;
    DmaPriority priority;
    bool circularMode;
};
```

#### Enums
```cpp
enum class DmaChannel {
    kChannel1 = 0, kChannel2 = 1, kChannel3 = 2, kChannel4 = 3,
    kChannel5 = 4, kChannel6 = 5, kChannel7 = 6, kChannel8 = 7
};

enum class DmaDirection {
    kPer2Mem = 0,
    kMem2Per = 1,
    kMem2Mem = 2
};

enum class DmaPriority {
    kLow = 0,
    kMedium = 1,
    kHigh = 2,
    kVeryHigh = 3
};

enum class DmaStatus {
    kIdle = 0,
    kBusy = 1,
    kComplete = 2,
    kError = 3
};
```

#### Example
```cpp
#include "mcal/Dma.h"

// Configure DMA
stm32::mcal::DmaConfig config = {
    stm32::mcal::kChannel1,
    stm32::mcal::kMem2Per,
    reinterpret_cast<uint32_t>(buffer),
    reinterpret_cast<uint32_t>(&USART1->DR),
    100,
    stm32::mcal::kMedium,
    false
};

stm32::mcal::DMA dma(config);
dma.Init();
dma.Enable();
```

## 🔧 HAL (Hardware Abstraction Layer)

### Timer

#### Classes
- **`Timer`**: Timer peripheral control

#### Constructor
```cpp
Timer(TimerInstance instance);
```

#### Functions
```cpp
// Initialize timer
bool Init();

// Start timer
void Start();

// Stop timer
void Stop();

// Set prescaler
void SetPrescaler(uint16_t prescaler);

// Set auto-reload value
void SetAutoReload(uint16_t value);

// Get counter value
uint16_t GetCounter();

// Enable interrupt
void EnableInterrupt(TimerInterrupt interrupt);
```

#### Enums
```cpp
enum class TimerInstance {
    kTIM1 = 0,
    kTIM2 = 1,
    kTIM3 = 2,
    kTIM4 = 3
};

enum class TimerInterrupt {
    kUpdate = 0,
    kCaptureCompare = 1,
    kTrigger = 2
};
```

### CAN (Controller Area Network)

#### Classes
- **`CAN`**: CAN peripheral control

#### Constructor
```cpp
CAN(const CanConfig& config);
```

#### Functions
```cpp
// Initialize CAN
bool Init();

// Send message
bool SendMessage(const CanMessage& message);

// Receive message
bool ReceiveMessage(CanMessage& message);

// Set filter
void SetFilter(const CanFilter& filter);
```

#### Configuration Structure
```cpp
struct CanConfig {
    CanInstance instance;
    uint32_t baud_rate;
    CanMode mode;
};

struct CanMessage {
    uint32_t id;
    bool extended_id;
    uint8_t data[8];
    uint8_t length;
};

struct CanFilter {
    uint32_t filter_id;
    uint32_t filter_mask;
    bool extended_id;
};
```

#### Enums
```cpp
enum class CanInstance {
    kCAN1 = 0,
    kCAN2 = 1
};

enum class CanMode {
    kNormal = 0,
    kLoopback = 1,
    kSilent = 2,
    kSilentLoopback = 3
};
```

## 🛠️ Utilities

### Bit Manipulation

#### Functions
```cpp
// Get number of ones in a value
constexpr uint32_t GetOnes(uint32_t value);

// Extract bits from value
constexpr uint32_t ExtractBits(uint32_t value, uint32_t start, uint32_t length);

// Write bits to value
constexpr uint32_t WriteBits(uint32_t value, uint32_t start, uint32_t length, uint32_t new_value);

// Set bits
constexpr uint32_t SetBits(uint32_t value, uint32_t mask);

// Clear bits
constexpr uint32_t ClearBits(uint32_t value, uint32_t mask);

// Set single bit
constexpr uint32_t SetBit(uint32_t value, uint32_t bit);

// Clear single bit
constexpr uint32_t ClearBit(uint32_t value, uint32_t bit);
```

### Array Template

#### Classes
- **`Array<T, Size>`**: Static array with bounds checking

#### Template
```cpp
template<typename T, size_t Size>
class Array {
public:
    // Constructor
    Array();
    
    // Access element
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    // Get size
    constexpr size_t size() const;
    
    // Get data pointer
    T* data();
    const T* data() const;
    
    // Fill array
    void fill(const T& value);
};
```

### String Class

#### Classes
- **`String`**: Dynamic string class

#### Functions
```cpp
// Constructor
String();
String(const char* str);

// Destructor
~String();

// Assignment
String& operator=(const String& other);
String& operator=(const char* str);

// Concatenation
String operator+(const String& other) const;
String& operator+=(const String& other);

// Length
size_t length() const;

// Get C-string
const char* c_str() const;
```

## 📋 Error Handling

### Return Values
Most functions return `bool` to indicate success/failure:
- `true`: Operation successful
- `false`: Operation failed

### Error Checking
```cpp
// Always check return values
if (!usart.Init()) {
    // Handle initialization error
    return -1;
}

// Check peripheral status
if (dma.IsTransferComplete()) {
    // Process completed transfer
}
```

## 🔍 Best Practices

### 1. Initialization Order
```cpp
// 1. Initialize RCC first
stm32::mcal::Rcc::Init();
stm32::mcal::Rcc::SetExternalClock(stm32::mcal::kHseCrystal);
stm32::mcal::Rcc::InitSysClock();

// 2. Enable peripheral clocks
stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);

// 3. Initialize peripherals
stm32::mcal::Gpio::Init();
stm32::mcal::Usart usart(config);
usart.Init();
```

### 2. Resource Management
```cpp
// Always check initialization
if (!peripheral.Init()) {
    // Handle error
    return;
}

// Use peripheral
peripheral.DoSomething();

// Cleanup if needed
peripheral.Deinit();
```

### 3. Performance Optimization
```cpp
// Use constexpr for compile-time constants
constexpr uint32_t BAUD_RATE = 9600;

// Use references to avoid copying
void ProcessData(const stm32::mcal::UsartConfig& config);

// Use static allocation
static stm32::mcal::Usart usart(config);
```

## 📞 Support

For questions about the API:
- Check the [Customer Guide](CUSTOMER_GUIDE.md)
- Review [Examples](EXAMPLES.md)
- Create an [Issue](https://github.com/abadr99/stm32f10xxx_cpp_interface/issues)

---

**This API reference is continuously updated. Check the latest version in the repository.**

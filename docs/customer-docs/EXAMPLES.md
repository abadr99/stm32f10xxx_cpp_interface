# STM32F10xxx C++ Interface Library - Examples

## 📚 Overview

This document provides comprehensive examples demonstrating how to use the STM32F10xxx C++ Interface Library in various scenarios.

## 🚀 Quick Start Examples

### 1. Basic GPIO Control

#### LED Blinking
```cpp
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure LED pin (PC13)
    stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
    stm32::mcal::Gpio::SetPinMode(led, stm32::mcal::PinMode::kOutputPushPull_10MHz);
    
    // Main loop
    while (1) {
        // Turn LED on
        stm32::mcal::Gpio::SetPinValue(led, stm32::mcal::DigitalVoltage::kHigh);
        
        // Delay
        for (volatile int i = 0; i < 1000000; i++);
        
        // Turn LED off
        stm32::mcal::Gpio::SetPinValue(led, stm32::mcal::DigitalVoltage::kLow);
        
        // Delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

#### Button Input with LED Output
```cpp
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure button pin (PA0) - input with pull-up
    stm32::mcal::Pin button(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin0);
    stm32::mcal::Gpio::SetPinMode(button, stm32::mcal::PinMode::kInputPullUp);
    
    // Configure LED pin (PC13) - output
    stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
    stm32::mcal::Gpio::SetPinMode(led, stm32::mcal::PinMode::kOutputPushPull_10MHz);
    
    // Main loop
    while (1) {
        // Read button state
        auto button_state = stm32::mcal::Gpio::GetPinValue(button);
        
        // Control LED based on button
        if (button_state == stm32::mcal::DigitalVoltage::kLow) {
            // Button pressed - turn LED on
            stm32::mcal::Gpio::SetPinValue(led, stm32::mcal::DigitalVoltage::kHigh);
        } else {
            // Button released - turn LED off
            stm32::mcal::Gpio::SetPinValue(led, stm32::mcal::DigitalVoltage::kLow);
        }
        
        // Small delay for debouncing
        for (volatile int i = 0; i < 10000; i++);
    }
    
    return 0;
}
```

### 2. USART Communication

#### Basic Serial Communication
```cpp
#include "mcal/Usart.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure USART pins (PA9 - TX, PA10 - RX)
    stm32::mcal::Pin tx_pin(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin9);
    stm32::mcal::Pin rx_pin(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin10);
    
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
    
    // Main loop
    while (1) {
        // Send message
        const char* message = "Hello, World!\r\n";
        for (int i = 0; message[i] != '\0'; i++) {
            usart.Transmit(message[i]);
        }
        
        // Delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

#### Echo Server
```cpp
#include "mcal/Usart.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure USART
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
    
    // Main loop
    while (1) {
        // Check if data is available
        if (usart.IsDataReady()) {
            // Read received byte
            uint8_t received_byte = usart.Receive();
            
            // Echo back the received byte
            usart.Transmit(received_byte);
            
            // Add newline for readability
            if (received_byte == '\r') {
                usart.Transmit('\n');
            }
        }
    }
    
    return 0;
}
```

### 3. ADC Reading

#### Single Channel ADC
```cpp
#include "mcal/Adc.h"
#include "mcal/Usart.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kADC1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure USART for output
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
    
    // Configure ADC
    stm32::mcal::AdcConfig adc_config = {
        stm32::mcal::kADC1,
        stm32::mcal::kRight,
        stm32::mcal::kChannel0,
        stm32::mcal::kSingle,
        stm32::mcal::kSoftware,
        stm32::mcal::kCycles_239_5
    };
    
    stm32::mcal::ADC adc(adc_config);
    adc.Init();
    
    // Main loop
    while (1) {
        // Start ADC conversion
        if (adc.StartSingleConversion()) {
            // Wait for conversion to complete
            while (!adc.IsConversionComplete());
            
            // Get result
            uint16_t adc_value = adc.GetConversionResult();
            
            // Convert to voltage (assuming 3.3V reference)
            float voltage = (adc_value * 3.3f) / 4095.0f;
            
            // Send result via USART
            char buffer[32];
            int len = snprintf(buffer, sizeof(buffer), "ADC: %d, Voltage: %.2fV\r\n", 
                              adc_value, voltage);
            
            for (int i = 0; i < len; i++) {
                usart.Transmit(buffer[i]);
            }
        }
        
        // Delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

#### Temperature Sensor Reading
```cpp
#include "mcal/Adc.h"
#include "mcal/Usart.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kADC1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
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
    
    // Configure ADC for temperature sensor (channel 16)
    stm32::mcal::AdcConfig adc_config = {
        stm32::mcal::kADC1,
        stm32::mcal::kRight,
        stm32::mcal::kChannel16,
        stm32::mcal::kSingle,
        stm32::mcal::kSoftware,
        stm32::mcal::kCycles_239_5
    };
    
    stm32::mcal::ADC adc(adc_config);
    adc.Init();
    
    // Main loop
    while (1) {
        // Read temperature
        float temperature = adc.GetTemperatureValue();
        
        // Send temperature via USART
        char buffer[32];
        int len = snprintf(buffer, sizeof(buffer), "Temperature: %.2f°C\r\n", temperature);
        
        for (int i = 0; i < len; i++) {
            usart.Transmit(buffer[i]);
        }
        
        // Delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

## 🔧 Advanced Examples

### 4. DMA with USART

#### DMA Transmit
```cpp
#include "mcal/Dma.h"
#include "mcal/Usart.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kDMA1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure USART
    stm32::mcal::UsartConfig usart_config = {
        stm32::mcal::kUsart1,
        stm32::mcal::kRxTx,
        stm32::mcal::kSb_1_,
        stm32::mcal::kDataBits_8_,
        stm32::mcal::kNo_Parity,
        stm32::mcal::kNone,
        115200
    };
    
    stm32::mcal::Usart usart(usart_config);
    usart.Init();
    
    // Configure DMA
    stm32::mcal::DmaConfig dma_config = {
        stm32::mcal::kChannel4,
        stm32::mcal::kMem2Per,
        reinterpret_cast<uint32_t>(message),
        reinterpret_cast<uint32_t>(&USART1->DR),
        sizeof(message) - 1,
        stm32::mcal::kMedium,
        false
    };
    
    stm32::mcal::DMA dma(dma_config);
    dma.Init();
    
    // Message to send
    const char message[] = "Hello from DMA!\r\n";
    
    // Main loop
    while (1) {
        // Start DMA transfer
        dma.Enable();
        
        // Wait for transfer to complete
        while (!dma.IsTransferComplete());
        
        // Disable DMA
        dma.Disable();
        
        // Delay
        for (volatile int i = 0; i < 5000000; i++);
    }
    
    return 0;
}
```

### 5. Timer Configuration

#### Timer-based LED Blinking
```cpp
#include "mcal/Timer.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kTIM2);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure LED pin
    stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
    stm32::mcal::Gpio::SetPinMode(led, stm32::mcal::PinMode::kOutputPushPull_10MHz);
    
    // Configure timer
    stm32::mcal::Timer timer(stm32::mcal::kTIM2);
    timer.Init();
    
    // Set timer for 1Hz (1 second interval)
    // Assuming 72MHz system clock
    timer.SetPrescaler(7200 - 1);  // 72MHz / 7200 = 10kHz
    timer.SetAutoReload(10000 - 1); // 10kHz / 10000 = 1Hz
    
    // Start timer
    timer.Start();
    
    // Main loop
    while (1) {
        // Check if timer has updated
        if (timer.IsUpdateFlagSet()) {
            // Clear update flag
            timer.ClearUpdateFlag();
            
            // Toggle LED
            stm32::mcal::Gpio::TogglePinValue(led);
        }
    }
    
    return 0;
}
```

### 6. SPI Communication

#### SPI Master
```cpp
#include "mcal/Spi.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kSPI1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure SPI pins
    // PA5 - SCK, PA6 - MISO, PA7 - MOSI
    stm32::mcal::Pin sck_pin(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin5);
    stm32::mcal::Pin miso_pin(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin6);
    stm32::mcal::Pin mosi_pin(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin7);
    stm32::mcal::Pin cs_pin(stm32::mcal::Port::kPortA, stm32::mcal::Pin::kPin4);
    
    // Configure SPI
    stm32::mcal::SpiConfig spi_config = {
        stm32::mcal::kSPI1,
        stm32::mcal::kMaster,
        stm32::mcal::kMode0,
        stm32::mcal::kMsbFirst,
        stm32::mcal::k8Bit,
        1000000  // 1MHz
    };
    
    stm32::mcal::SPI spi(spi_config);
    spi.Init();
    
    // Data to send
    uint8_t tx_data[] = {0x01, 0x02, 0x03, 0x04};
    uint8_t rx_data[4];
    
    // Main loop
    while (1) {
        // Select slave
        stm32::mcal::Gpio::SetPinValue(cs_pin, stm32::mcal::DigitalVoltage::kLow);
        
        // Transmit data
        for (int i = 0; i < 4; i++) {
            rx_data[i] = spi.Transmit(tx_data[i]);
        }
        
        // Deselect slave
        stm32::mcal::Gpio::SetPinValue(cs_pin, stm32::mcal::DigitalVoltage::kHigh);
        
        // Delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

## 🎯 Real-World Examples

### 7. Data Logger

#### Simple Data Logger with USART
```cpp
#include "mcal/Adc.h"
#include "mcal/Usart.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "utils/Array.h"

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kADC1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure USART
    stm32::mcal::UsartConfig usart_config = {
        stm32::mcal::kUsart1,
        stm32::mcal::kRxTx,
        stm32::mcal::kSb_1_,
        stm32::mcal::kDataBits_8_,
        stm32::mcal::kNo_Parity,
        stm32::mcal::kNone,
        115200
    };
    
    stm32::mcal::Usart usart(usart_config);
    usart.Init();
    
    // Configure ADC
    stm32::mcal::AdcConfig adc_config = {
        stm32::mcal::kADC1,
        stm32::mcal::kRight,
        stm32::mcal::kChannel0,
        stm32::mcal::kSingle,
        stm32::mcal::kSoftware,
        stm32::mcal::kCycles_239_5
    };
    
    stm32::mcal::ADC adc(adc_config);
    adc.Init();
    
    // Data buffer
    stm32::utils::Array<uint16_t, 100> data_buffer;
    uint32_t sample_count = 0;
    
    // Main loop
    while (1) {
        // Take ADC sample
        if (adc.StartSingleConversion()) {
            while (!adc.IsConversionComplete());
            
            uint16_t sample = adc.GetConversionResult();
            data_buffer[sample_count % 100] = sample;
            sample_count++;
            
            // Send data via USART
            char buffer[64];
            int len = snprintf(buffer, sizeof(buffer), 
                              "Sample %lu: %d (%.2fV)\r\n", 
                              sample_count, sample, 
                              (sample * 3.3f) / 4095.0f);
            
            for (int i = 0; i < len; i++) {
                usart.Transmit(buffer[i]);
            }
        }
        
        // Delay between samples
        for (volatile int i = 0; i < 100000; i++);
    }
    
    return 0;
}
```

### 8. Simple Protocol Handler

#### Command Parser with USART
```cpp
#include "mcal/Usart.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "utils/Array.h"

class CommandHandler {
private:
    stm32::utils::Array<char, 64> command_buffer;
    uint8_t buffer_index;
    stm32::mcal::Usart* usart;
    stm32::mcal::Pin* led;
    
public:
    CommandHandler(stm32::mcal::Usart* uart, stm32::mcal::Pin* led_pin) 
        : buffer_index(0), usart(uart), led(led_pin) {}
    
    void Process() {
        if (usart->IsDataReady()) {
            char received = usart->Receive();
            
            if (received == '\r' || received == '\n') {
                // End of command
                command_buffer[buffer_index] = '\0';
                ExecuteCommand();
                buffer_index = 0;
            } else if (buffer_index < 63) {
                // Add to buffer
                command_buffer[buffer_index++] = received;
            }
        }
    }
    
private:
    void ExecuteCommand() {
        if (strcmp(command_buffer.data(), "LED_ON") == 0) {
            stm32::mcal::Gpio::SetPinValue(*led, stm32::mcal::DigitalVoltage::kHigh);
            SendResponse("LED turned ON");
        } else if (strcmp(command_buffer.data(), "LED_OFF") == 0) {
            stm32::mcal::Gpio::SetPinValue(*led, stm32::mcal::DigitalVoltage::kLow);
            SendResponse("LED turned OFF");
        } else if (strcmp(command_buffer.data(), "STATUS") == 0) {
            SendResponse("System OK");
        } else {
            SendResponse("Unknown command");
        }
    }
    
    void SendResponse(const char* response) {
        for (int i = 0; response[i] != '\0'; i++) {
            usart->Transmit(response[i]);
        }
        usart->Transmit('\r');
        usart->Transmit('\n');
    }
};

int main() {
    // Initialize system
    stm32::mcal::Rcc::Init();
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPA);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
    stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kUSART1);
    
    // Initialize GPIO
    stm32::mcal::Gpio::Init();
    
    // Configure LED
    stm32::mcal::Pin led(stm32::mcal::Port::kPortC, stm32::mcal::Pin::kPin13);
    stm32::mcal::Gpio::SetPinMode(led, stm32::mcal::PinMode::kOutputPushPull_10MHz);
    
    // Configure USART
    stm32::mcal::UsartConfig usart_config = {
        stm32::mcal::kUsart1,
        stm32::mcal::kRxTx,
        stm32::mcal::kSb_1_,
        stm32::mcal::kDataBits_8_,
        stm32::mcal::kNo_Parity,
        stm32::mcal::kNone,
        115200
    };
    
    stm32::mcal::Usart usart(usart_config);
    usart.Init();
    
    // Create command handler
    CommandHandler handler(&usart, &led);
    
    // Main loop
    while (1) {
        handler.Process();
    }
    
    return 0;
}
```

## 📋 Best Practices

### 1. Error Handling
```cpp
// Always check return values
if (!peripheral.Init()) {
    // Handle error
    return -1;
}

// Check status before operations
if (peripheral.IsReady()) {
    peripheral.DoOperation();
}
```

### 2. Resource Management
```cpp
// Initialize in correct order
stm32::mcal::Rcc::Init();
stm32::mcal::Rcc::Enable(stm32::mcal::Peripheral::kIOPC);
stm32::mcal::Gpio::Init();

// Use static allocation when possible
static stm32::mcal::Usart usart(config);
```

### 3. Performance Optimization
```cpp
// Use constexpr for constants
constexpr uint32_t BAUD_RATE = 9600;

// Minimize function calls in loops
for (int i = 0; i < 1000; i++) {
    // Avoid repeated function calls
    static bool initialized = false;
    if (!initialized) {
        peripheral.Init();
        initialized = true;
    }
}
```

## 📞 Support

For more examples and help:
- Check the [API Reference](API_REFERENCE.md)
- Review the [Customer Guide](CUSTOMER_GUIDE.md)
- Create an [Issue](https://github.com/abadr99/stm32f10xxx_cpp_interface/issues)

---

**These examples demonstrate common use cases. Adapt them to your specific needs!**

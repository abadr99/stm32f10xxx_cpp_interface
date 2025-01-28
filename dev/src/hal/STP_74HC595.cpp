/**
 * @file STP_74HC595.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>

#include "utils/BitManipulation.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "mcal/Rcc.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Systick.h"
#include "hal/STP_74HC595.h"

#define SR_CLK_PERIOD_US   (10)

using namespace stm32;
using namespace stm32::type;
using namespace stm32::util;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::hal::shift_register;


STP_74HC595::STP_74HC595(const Pin& serialInputPin, const Pin& shiftClkPin, const Pin& storageClk)
: pins_{ .serialInputPin = serialInputPin, 
         .shiftClkPin = shiftClkPin, 
         .storageClkPin = storageClk } 
    { }

void STP_74HC595::InitializePins() { 
    // Enable RCC for all used GPIO ports 
    Rcc::Enable(MapPortToPeripheral((pins_.serialInputPin).GetPort())); 
    if (pins_.serialInputPin.GetPort() != pins_.shiftClkPin.GetPort()) { 
        Rcc::Enable(MapPortToPeripheral(pins_.shiftClkPin.GetPort())); 
    } 
    if (pins_.storageClkPin.GetPort() != pins_.serialInputPin.GetPort() &&  
        pins_.storageClkPin.GetPort() != pins_.shiftClkPin.GetPort()) { 
        Rcc::Enable(MapPortToPeripheral(pins_.storageClkPin.GetPort())); 
    }
        // Set shift register pins as output pins
    STM32_ASSERT(pins_.serialInputPin.IsOutput(), CONFIG_ERROR(_STP, _CONFIG));
    STM32_ASSERT(pins_.shiftClkPin.IsOutput(), CONFIG_ERROR(_STP, _CONFIG));
    STM32_ASSERT(pins_.storageClkPin.IsOutput(), CONFIG_ERROR(_STP, _CONFIG));
    Gpio::Set(pins_.serialInputPin);
    Gpio::Set(pins_.shiftClkPin);
    Gpio::Set(pins_.storageClkPin);
    
    // Set pins as low
    Gpio::SetPinValue(pins_.serialInputPin, DigitalVoltage::kLow);
    Gpio::SetPinValue(pins_.shiftClkPin,    DigitalVoltage::kLow);
        Gpio::SetPinValue(pins_.storageClkPin,     DigitalVoltage::kLow);
}


void STP_74HC595::Pulse() {
    Gpio::SetPinValue(pins_.shiftClkPin, DigitalVoltage::kHigh);
    Systick::Delay_us(SR_CLK_PERIOD_US);
    Gpio::SetPinValue(pins_.shiftClkPin, DigitalVoltage::kLow);
    Systick::Delay_us(SR_CLK_PERIOD_US);
}

void STP_74HC595::Write(ShiftRegisterWidth val) {
    // -- 1] Disable Latch until we fill storage register
    Gpio::SetPinValue(pins_.storageClkPin, DigitalVoltage::kLow);

    // -- 2] Write data to shift register
    for (uint8_t i = 0 ; i < 8 ; ++i) {
        Pulse();
        DigitalVoltage state = static_cast<DigitalVoltage>(util::ExtractBit(val, i)); 
        Gpio::SetPinValue(pins_.serialInputPin, state);
    }
    // -- 3] output data to storage register
    Gpio::SetPinValue(pins_.storageClkPin, DigitalVoltage::kHigh);
}

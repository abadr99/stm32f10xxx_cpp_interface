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
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Systick.h"
#include "hal/STP_74HC595.h"

#define SR_CLK_PERIOD_US   (10)

using namespace stm32;
using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::hal::shift_register;


STP_74HC595::STP_74HC595(const Pin& serialInputPin, const Pin& shiftClkPin, const Pin& storageClk)
: pins_{ .serialInputPin = serialInputPin, 
         .shiftClkPin = shiftClkPin, 
         .storageClk = storageClk } 
    { 
        // Set shift register pins as output pins
        STM32_ASSERT(pins_.serialInputPin.IsOutput(), CONFIG_ERROR(_STP, _CONFIG));
        STM32_ASSERT(pins_.shiftClkPin.IsOutput(), CONFIG_ERROR(_STP, _CONFIG));
        STM32_ASSERT(pins_.storageClk.IsOutput(), CONFIG_ERROR(_STP, _CONFIG));

        Gpio::Set(pins_.serialInputPin);
        Gpio::Set(pins_.shiftClkPin);
        Gpio::Set(pins_.storageClk);
        
        // Set pins as low
        Gpio::SetPinValue(pins_.serialInputPin, DigitalVoltage::kLow);
        Gpio::SetPinValue(pins_.shiftClkPin,    DigitalVoltage::kLow);
        Gpio::SetPinValue(pins_.storageClk,     DigitalVoltage::kLow);
    }


void STP_74HC595::Pulse() {
    Gpio::SetPinValue(pins_.shiftClkPin, DigitalVoltage::kHigh);
    Systick::Delay_us(SR_CLK_PERIOD_US);
    Gpio::SetPinValue(pins_.shiftClkPin, DigitalVoltage::kLow);
    Systick::Delay_us(SR_CLK_PERIOD_US);
}

void STP_74HC595::Write(ShiftRegisterWidth val) {
    // -- 1] Disable Latch until we fill storage register
    Gpio::SetPinValue(pins_.storageClk, DigitalVoltage::kLow);

    // -- 2] Write data to shift register
    for (uint8_t i = 0 ; i < 8 ; ++i) {
        Pulse();
        DigitalVoltage state = static_cast<DigitalVoltage>(util::ExtractBit(val, i)); 
        Gpio::SetPinValue(pins_.serialInputPin, state);
    }
    // -- 3] output data to storage register
    Gpio::SetPinValue(pins_.storageClk, DigitalVoltage::kHigh);
}

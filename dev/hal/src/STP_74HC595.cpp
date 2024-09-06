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

#include "BitManipulation.h"
#include "Assert.h"
#include "Pin.h"
#include "Gpio.h"
#include "Systick.h"
#include "STP_74HC595.h"

#define SR_CLK_PERIOD_US   (10)

using namespace stm32::util;
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
        STM32_ASSERT(pins_.serialInputPin.IsOutput());
        STM32_ASSERT(pins_.shiftClkPin.IsOutput());
        STM32_ASSERT(pins_.storageClk.IsOutput());

        Gpio::Set(pins_.serialInputPin);
        Gpio::Set(pins_.shiftClkPin);
        Gpio::Set(pins_.storageClk);
        
        // Set pins as low
        Gpio::SetPinValue(pins_.serialInputPin, Gpio::State::kLow);
        Gpio::SetPinValue(pins_.shiftClkPin,    Gpio::State::kLow);
        Gpio::SetPinValue(pins_.storageClk,     Gpio::State::kLow);
    }


void STP_74HC595::Pulse() {
    Gpio::SetPinValue(pins_.shiftClkPin, Gpio::State::kHigh);
    Systick::Delay_us(SR_CLK_PERIOD_US);
    Gpio::SetPinValue(pins_.shiftClkPin, Gpio::State::kLow);
    Systick::Delay_us(SR_CLK_PERIOD_US);
}

void STP_74HC595::Write(ShiftRegisterWidth val) {
    // -- 1] Disable Latch until we fill storage register
    Gpio::SetPinValue(pins_.storageClk, Gpio::State::kLow);

    // -- 2] Write data to shift register
    for (uint8_t i = 0 ; i < 8 ; ++i) {
        Pulse();
        Gpio::State state = static_cast<Gpio::State>(ExtractBit(val, i)); 
        Gpio::SetPinValue(pins_.serialInputPin, state);
    }
    // -- 3] output data to storage register
    Gpio::SetPinValue(pins_.storageClk, Gpio::State::kHigh);
}

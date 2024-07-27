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

#include "Pin.h"
#include "Gpio.h"
#include "Systick.h"
#include "STP_74HC595.h"

#define SR_CLK_PERIOD_US   (10)

using namespace stm32::utils::bit_manipulation;
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
        Gpio::SetOutputMode(pins_.serialInputPin, OutputMode::kPushPull_2MHZ);
        Gpio::SetOutputMode(pins_.shiftClkPin,    OutputMode::kPushPull_2MHZ);
        Gpio::SetOutputMode(pins_.storageClk,     OutputMode::kPushPull_2MHZ);
        
        // Set pins as low
        Gpio::SetPinValue(pins_.serialInputPin, State::kLow);
        Gpio::SetPinValue(pins_.shiftClkPin,    State::kLow);
        Gpio::SetPinValue(pins_.storageClk,     State::kLow);
    }


void STP_74HC595::Pulse() {
    Gpio::SetPinValue(pins_.shiftClkPin, State::kHigh);
    Systick::Delay_us(SR_CLK_PERIOD_US);
    Gpio::SetPinValue(pins_.shiftClkPin, State::kLow);
    Systick::Delay_us(SR_CLK_PERIOD_US);
}

void STP_74HC595::Write(ShiftRegisterWidth val) {
    // -- 1] Disable Latch until we fill storage register
    Gpio::SetPinValue(pins_.storageClk, State::kLow);

    // -- 2] Write data to shift register
    for (uint8_t i = 0 ; i < 8 ; ++i) {
        Pulse();
        State state = static_cast<State>(ExtractBits(val, i)); 
        Gpio::SetPinValue(pins_.serialInputPin, state);
    }
    // -- 3] output data to storage register
    Gpio::SetPinValue(pins_.storageClk, State::kHigh);
}

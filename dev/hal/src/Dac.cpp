/**
 * @file DAC.cpp
 * @brief noura36
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Pin.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Systick.h"
#include "Array.h"
#include "Assert.h"
#include "BitManipulation.h"
#include "Dac.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::dev::mcal::gpio;
using  namespace stm32::dev::mcal::rcc;
using  namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::hal::dac;

Dac::Dac(Array<Pin, 8> dacPins, CLKSource clock) : dacPins_(dacPins), clock_(clock) { 
    for (uint8_t i = 0; i < dacPins_.Size(); i++) {
        STM32_ASSERT(dacPins_[i].IsAnalog());
        STM32_ASSERT(dacPins_[i].IsInput());
        switch (dacPins_[i].GetPort()) {
            case kPortA: Rcc::Enable(Peripheral::kIOPA); break;
            case kPortB: Rcc::Enable(Peripheral::kIOPB); break;
            case kPortC: Rcc::Enable(Peripheral::kIOPC); break;
            default:break;
        }
    }
    for (uint8_t i = 0; i < dacPins_.Size(); i++) {
        Gpio::Set(dacPins_[i]);
    }
    Systick::Enable(clock_);
}
void Dac::DAC_Play(uint32_t* songRaw, uint32_t songLength) {
    static uint32_t count = 0;
    if (count >= songLength) {
        count = 0;
    }
    for (uint8_t i = 0; i < dacPins_.Size(); i++) {
        uint32_t data = songRaw[count];
        Gpio::SetPinValue(dacPins_[i], static_cast<Gpio::State>(ExtractBit<uint32_t>(data, i)));
    }
    count++;
}
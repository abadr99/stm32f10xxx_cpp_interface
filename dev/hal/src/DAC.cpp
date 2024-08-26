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
#include "Systick.h"
#include "Array.h"
#include "Assert.h"
#include "BitManipulation.h"
#include "DAC.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::dev::mcal::gpio;
using  namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::hal::dac;

Dac::Dac(Array<Pin, 8> dacPins, CLKSource clock) : dacPins_(dacPins), clock_(clock) { 
    for (uint8_t i = 0; i < dacPins.Size(); i++) {
        STM32_ASSERT(dacPins[i].IsAnalog());
        STM32_ASSERT(dacPins[i].IsInput());
    }
    for (uint8_t i = 0; i < dacPins.Size(); i++) {
        Gpio::Set(dacPins[i]);
    }
    Systick::Enable(clock);
}
void Dac::DAC_Play(const Array<Pin, 8>& dacPins, uint32_t* songRaw, uint32_t songLength) {
    static uint32_t count = 0;
    if (count >= songLength) {
        count = 0;
    }
    for (uint8_t i = 0; i < dacPins.Size(); i++) {
        uint32_t data = songRaw[count];
        Gpio::SetPinValue(dacPins[i], static_cast<Gpio::State>(ExtractBits<uint32_t>(data, i)));
    }
    count++;
}

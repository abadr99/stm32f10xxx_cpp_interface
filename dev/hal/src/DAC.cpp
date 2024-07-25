/**
 * @file DAC.cpp
 * @brief noura36
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <cstdlib>
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "mcal/inc/Systick.h"
#include "utils/inc/Array.h"
#include "hal/inc/DAC.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::dac;

void Dac::DAC_Init(const Array<Pin, 8>& dacPins, CLKSource clock) {
    for (uint8_t i =0; i < dacPins.Size(); i++) {
        Gpio::SetOutputMode(dacPins[i], OutputMode::kPushPull_2MHZ);
        Systick::Enable(clock);
    }
}
void Dac::DAC_Play(const Array<Pin, 8>& dacPins, uint32_t* songRaw, uint32_t songLength) {
    static uint32_t count = 0;
    if (count == songLength) {
        count = 0;
    }
    for (uint8_t i =0; i < dacPins.Size(); i++) {
        uint32_t data = songRaw[count];
        Gpio::SetPinValue(dacPins[i], static_cast<State> ((data >> i)&1));
    }
    count++;
}

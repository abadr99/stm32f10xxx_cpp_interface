/**
 * @file DAC.cpp
 * @brief noura36
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Systick.h"
#include "utils/Array.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "utils/BitManipulation.h"
#include "hal/Dac.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::util;
using namespace stm32::dev::hal::dac;

Dac::Dac(const Array<Pin, 8>& dacPins, CLKSource clock) : dacPins_(dacPins), clock_(clock) { 
    InitializePins();
    Systick::Enable(clock_);
}

void Dac::DAC_Play(uint32_t* songRaw, uint32_t songLength) {
    static uint32_t count = 0;
    if (count >= songLength) {
        count = 0;
    }
    for (uint8_t i = 0; i < dacPins_.Size(); i++) {
        uint32_t data = songRaw[count];
        Gpio::SetPinValue(dacPins_[i], static_cast<DigitalVoltage>(ExtractBit<uint32_t>(data, i)));
    }
    count++;
}

void Dac::InitializePins() {
    for (uint8_t i = 0; i < dacPins_.Size(); i++) {
    STM32_ASSERT(dacPins_[i].IsAnalog() && dacPins_[i].IsInput(), CONFIG_ERROR(_DAC, _CONFIG));
    Rcc::Enable(MapPortToPeripheral(dacPins_[i].GetPort()));
    Gpio::Set(dacPins_[i]);
    }
}

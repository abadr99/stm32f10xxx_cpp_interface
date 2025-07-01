/**
 * @file DC_Motor.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "utils/BitManipulation.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "hal/DC_Motor.h"
#include "utils/Util.h"
#include "mcal/Rcc.h"
#include "mcal/Timer.h"

using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::timer;
using namespace stm32::dev::hal::dc_motor;

DC_Motor::DC_Motor(const Pin& pin1, const Pin& pin2) 
        : pin1_(pin1) , pin2_(pin2) {
    // STM32_ASSERT(pin1.IsOutput(), CONFIG_ERROR(_MOTOR, _CONFIG));
    // STM32_ASSERT(pin2.IsOutput(), CONFIG_ERROR(_MOTOR, _CONFIG));
    Gpio::Set(pin1_);
    Gpio::Set(pin2_);
}

void DC_Motor::ClockWise() {
    Gpio::SetPinValue(pin1_, kHigh);
    Gpio::SetPinValue(pin2_, kLow);
}

void DC_Motor::AntiClockWise() {
    Gpio::SetPinValue(pin1_, kLow);
    Gpio::SetPinValue(pin2_, kHigh);
}

void DC_Motor::Stop() {
    Gpio::SetPinValue(pin1_, kLow);
    Gpio::SetPinValue(pin2_, kLow);
}

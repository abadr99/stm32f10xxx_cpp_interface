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
#include "BitManipulation.h"
#include "Types.h"
#include "Assert.h"
#include "Pin.h"
#include "Gpio.h"
#include "DC_Motor.h"

using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::dc_motor;

DC_Motor::DC_Motor(Pin pin1, Pin pin2) : pin1(pin1) , pin2(pin2) {
    STM32_ASSERT(pin1.IsOutput());
    STM32_ASSERT(pin2.IsOutput());
    Gpio::Set(pin1);
    Gpio::Set(pin2);
}

void DC_Motor::ClockWise() {
    Gpio::SetPinValue(pin1, DigitalVoltage::kHigh);
    Gpio::SetPinValue(pin2, DigitalVoltage::kLow);
}

void DC_Motor::AntiClockWise() {
    Gpio::SetPinValue(pin1, DigitalVoltage::kLow);
    Gpio::SetPinValue(pin2, DigitalVoltage::kHigh);
}

void DC_Motor::Stop() {
    Gpio::SetPinValue(pin1, DigitalVoltage::kLow);
    Gpio::SetPinValue(pin2, DigitalVoltage::kLow);
}

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

#include "Pin.h"
#include "Gpio.h"
#include "DC_Motor.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::dc_motor;

DC_Motor::DC_Motor(Pin pin1, Pin pin2) : pin1(pin1) , pin2(pin2) {
    Gpio::SetOutputMode(pin1, OutputMode::kPushPull_2MHZ);
    Gpio::SetOutputMode(pin2, OutputMode::kPushPull_2MHZ);
}
void DC_Motor::ClockWise() {
    Gpio::SetPinValue(pin1, kHigh);
    Gpio::SetPinValue(pin2, kLow);
}
void DC_Motor::AntiClockWise() {
    Gpio::SetPinValue(pin1, kLow);
    Gpio::SetPinValue(pin2, kHigh);
}
void DC_Motor::Stop() {
    Gpio::SetPinValue(pin1, kLow);
    Gpio::SetPinValue(pin2, kLow);
}

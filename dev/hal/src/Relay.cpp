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
#include "Relay.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::relay;

Relay::Relay(Pin relayPin) : relayPin(relayPin) {
    Gpio::SetOutputMode(relayPin, OutputMode::kPushPull_2MHZ);
}
void Relay::Control(State state) {
    switch (state) {
    case kHigh:Gpio::SetPinValue(relayPin, kHigh); break;
    case kLow:Gpio::SetPinValue(relayPin, kLow); break;
    }
}

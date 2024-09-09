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
#include "Relay.h"

using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::relay;

Relay::Relay(Pin relayPin) : relayPin(relayPin) {
    STM32_ASSERT(relayPin.IsOutput());
    Gpio::Set(relayPin);
}

void Relay::Control(DigitalVoltage state) {
    Gpio::SetPinValue(relayPin, state);
}

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
#include "hal/Relay.h"

using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::relay;


Relay::Relay(Pin relayPin) : relayPin(relayPin) {
    STM32_ASSERT(relayPin.IsOutput(), CONFIG_ERROR(_RELAY, _CONFIG));
    Gpio::Set(relayPin);
}

void Relay::Control(DigitalVoltage state) {
    Gpio::SetPinValue(relayPin, state);
}

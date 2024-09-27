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
#include "utils/Util.h"
#include "mcal/Rcc.h"
using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::relay;

Relay::Relay(const Pin& relayPin) : relayPin(relayPin) {
    STM32_ASSERT(relayPin.IsOutput(), CONFIG_ERROR(_RELAY, _CONFIG));
    Rcc::Enable(MapPortToPeripheral(relayPin.GetPort()));
    Gpio::Set(relayPin);
}

void Relay::Control(DigitalVoltage state) {
    Gpio::SetPinValue(relayPin, state);
}

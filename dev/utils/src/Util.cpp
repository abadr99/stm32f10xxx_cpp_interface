/**
 * @file Util.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Assert.h"

#include "Pin.h"
#include "Rcc.h"
#include "Gpio.h"

#include "Util.h"

using Port = stm32::dev::mcal::pin::Port;
using Peripheral = stm32::dev::mcal::rcc::Peripheral;
using namespace stm32::utils;

Peripheral MapPortToPeripheral(Port port) {
    switch (port) {
        case Port::kPortA:    return Peripheral::kIOPA;
        case Port::kPortB:    return Peripheral::kIOPB;
        case Port::kPortC:    return Peripheral::kIOPC;
    }
    STM32_ASSERT(1);
    return Peripheral::kUnknown;
}

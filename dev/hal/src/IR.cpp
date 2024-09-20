/**
 * @file IR.cpp
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "Assert.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/IR.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::ir;


IR::IR(const Pin& IrPin) : IrPin_(IrPin) {
    STM32_ASSERT(IrPin.IsInput(), CONFIG_ERROR(_IR, _CONFIG));
    Gpio::Set(IrPin);
}

IR::IrState IR::GetIrStatus() {
    return Gpio::GetPinValue(IrPin_);
}

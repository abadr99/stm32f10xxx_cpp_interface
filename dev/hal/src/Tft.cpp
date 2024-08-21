/**
 * @file Tft.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */


#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitManipulation.h"
#include "Rcc.h"
#include "Assert.h"
#include "Pin.h"
#include "Gpio.h"
#include "Spi.h"
#include "Systick.h"
#include "Tft.h"
using namespace stm32::utils::bit_manipulation;
using namespace stm32::utils::types;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::spi;
using namespace stm32::dev::hal::tft;

Tft::Tft(Pin A0, Pin rst, Spi SdSpi) : A0(A0), rst(rst), SdSpi(SdSpi) {
}
void Tft::SendCommand(uint8_t command) {
//  Gpio::SetPinValue(A0, Gpio::kLow);
SdSpi.Write(command);
}

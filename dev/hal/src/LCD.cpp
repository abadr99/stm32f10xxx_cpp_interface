/**
 * @file LCD.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "BitManipulation.h"

#include "Pin.h"
#include "Gpio.h"
#include "Systick.h"
#include "Array.h"
#include "LCD.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::hal::lcd;
using namespace stm32::utils::array;

void LCD::SendFallingEdgePulse(const LCD_Config &config) {
    Gpio::SetPinValue(config.ENpin, kHigh);
    Systick::Delay_ms(1);
    Gpio::SetPinValue(config.ENpin, kLow);
    Systick::Delay_ms(1);
}

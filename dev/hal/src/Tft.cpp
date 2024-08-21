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
#include "mcal/inc/stm32f103xx.h"
#include "Pin.h"
#include "Gpio.h"
#include "Spi.h"
#include "Systick.h"
#include "Tft.h"

using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::spi;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::hal::tft;

Tft::Tft(Pin A0, Pin rst, Spi TFtSpi) : A0(A0), rst(rst), TFtSpi(TFtSpi) {
    Gpio::Set(A0);
    Gpio::Set(rst);
    //  Reset pulse
    Gpio::SetPinValue(rst, Gpio::kHigh);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(rst, Gpio::kLow);
    Systick::Delay_ms(2);
    Gpio::SetPinValue(rst, Gpio::kHigh);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(rst, Gpio::kLow);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(rst, Gpio::kHigh);
    Systick::Delay_ms(120000);
    //  SleepOut
    SendCommand(kSLPOUT);
    Systick::Delay_ms(150);
    //  Color mode
    SendCommand(kCOLMOD);
    SendCommand(kCOLMOD_P);
    //  Display on
    SendCommand(kDISPON);
}
void Tft::SendCommand(uint8_t command) {
    Gpio::SetPinValue(A0, Gpio::kLow);
    TFtSpi.Write(command);
}
void Tft::SendData(uint8_t data) {
    Gpio::SetPinValue(A0, Gpio::kHigh);
    TFtSpi.Write(data);
}

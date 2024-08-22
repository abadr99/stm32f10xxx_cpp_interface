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
#include "Array.h"
#include "Tft.h"

using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::spi;
using namespace stm32::dev::mcal::systick;
using namespace stm32::utils::array;
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
void Tft::DisplayImage(const Array<uint16_t, 20480> image) {
    uint8_t data;
    //  Set X address
    SendCommand(kCASET);
    SendData(0);
    SendData(0);
    SendData(0);
    SendData(127);
    //  Set Y address
    SendCommand(kRASET);
    SendData(0);
    SendData(0);
    SendData(0);
    SendData(159);
    //  Memory write
    SendCommand(kRAWMR);    //  This tells the display that pixel data will follow.
    for (uint16_t counter = 0; counter < image.Size(); counter++) {
        data = image[counter] >> 8;
        //  write high byte
        SendData(data);
        //  write low byte
        data = image[counter] & 0x00ff;
        SendData(data);
    }
}
void Tft::FillColor(TftColors color) {
    uint8_t data;
    //  Set X address
    SendCommand(kCASET);
    SendData(0);
    SendData(0);
    SendData(0);
    SendData(127);
    //  Set Y address
    SendCommand(kRASET);
    SendData(0);
    SendData(0);
    SendData(0);
    SendData(159);
    //  Memory write
    SendCommand(kRAWMR);    //  This tells the display that pixel data will follow.
    for (uint16_t counter = 0; counter < 20480; counter++) {
        data = color >> 8;
        //  write high byte
        SendData(data);
        //  write low byte
        data = color & 0x00ff;
        SendData(data);
    }
}

/**
 * @file Tft.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-23
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
    Reset();
    //  SleepOut
    SendCommand(kSLPOUT);
    Systick::Delay_ms(150);
    //  Color mode
    SendCommand(kCOLMOD);
    SendCommand(RGB565);
    //  Display on
    SendCommand(kDISPON);
}
void Tft::Reset() {
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
}
void Tft::DisplayImage(const Array<uint16_t, 20480> image) {
    SetAddress(0, 127, 0, 159);
    for (uint16_t counter = 0; counter < image.Size(); counter++) {
        SetPixel(image[counter]);
    }
}
void Tft::DrawRectangle(uint8_t hight, uint8_t width, uint8_t xaxis, uint8_t yaxis, TftColors color) {  //  NOLINT
    DrawHLine(xaxis, yaxis, width, color);
    DrawVLine(xaxis, yaxis, hight, color);
    DrawHLine(xaxis, hight + yaxis, width, color);
    DrawVLine(xaxis + width, yaxis, hight, color);
}
void Tft::SendCommand(uint8_t command) {
    Gpio::SetPinValue(A0, Gpio::kLow);
    TFtSpi.Write(command);
}
void Tft::SendData(uint8_t data) {
    Gpio::SetPinValue(A0, Gpio::kHigh);
    TFtSpi.Write(data);
}
void Tft::SetAddress(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY) {
    if ((startX < 127) && (startY < 159)) {
        //  Set X address
        SendCommand(kCASET);
        //  Start byte
        SendData(startX >> 8);  //  MS byte
        SendData(startX);
        //  Stop byte
        SendData(endX >> 8);
        SendData(endX);
        //  Set Y address
        SendCommand(kRASET);
        //  Start byte
        SendData(startY >> 8);  //  MS byte
        SendData(startY);
        //  Stop byte
        SendData(endY >> 8);
        SendData(endY);
        //  Memory write
        SendCommand(kRAWMR);    //  This tells the display that pixel data will follow.
    }
}
void Tft::SetPixel(uint16_t pixel) {
    //  write high byte
    SendData(pixel >> 8);
    //  write low byte
    SendData(pixel & 0x00ff);
}
void Tft::DrawHLine(uint8_t xaxis, uint8_t yaxis, uint8_t length, TftColors color) {
    for (; length > 0; length --) {
        SendCommand(kCASET);
        SendData(xaxis);
        SendData(xaxis);
        SendCommand(kRASET);
        SendData(yaxis);
        SendData(yaxis);
        SendCommand(kRAWMR);
        SetPixel(color);
        xaxis++;
    }
}
void Tft::DrawVLine(uint8_t xaxis, uint8_t yaxis, uint8_t length, TftColors color) {
    for (; length > 0; length --) {
        SendCommand(kCASET);
        SendData(xaxis);
        SendData(xaxis);
        SendCommand(kRASET);
        SendData(yaxis);
        SendData(yaxis);
        SendCommand(kRAWMR);
        SetPixel(color);
        yaxis++;
    }
}

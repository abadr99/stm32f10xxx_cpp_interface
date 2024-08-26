/**
 * @file Tft.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mcal/inc/stm32f103xx.h"
#include "BitManipulation.h"
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
using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::hal::tft;

Tft::Tft(const TftConfig& config) : config_(config) {
    InitializeResolution();
    Gpio::Set(config_.A0);
    Gpio::Set(config_.rst);
    //  Reset pulse
    Reset();
    //  SleepOut
    SendCommand(kSLPOUT);
    Systick::Delay_ms(150);
    //  Color mode
    SendCommand(kCOLMOD);
    SendData(RGB565);
    //  Display on
    SendCommand(kDISPON);
}
void Tft::InitializeResolution() {
    switch (config_.resolution) {
        case k128x160:
            config_.width = 128;
            config_.height = 160;
            break;
        case k240x320:
            config_.width = 240;
            config_.height = 320;
            break;
        case k320x480:
            config_.width = 320;
            config_.height = 480;
            break;
        case k480x800:
            config_.width = 480;
            config_.height = 800;
            break;
        default:
            config_.width = 128;  // Default to 128x160
            config_.height = 160;
            break;
    }
}
void Tft::Reset() {
    Gpio::SetPinValue(config_.rst, Gpio::kHigh);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(config_.rst, Gpio::kLow);
    Systick::Delay_ms(2);
    Gpio::SetPinValue(config_.rst, Gpio::kHigh);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(config_.rst, Gpio::kLow);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(config_.rst, Gpio::kHigh);
    Systick::Delay_ms(120000);
}
void Tft::DisplayImage(const Array<uint16_t, 20480> image) {
    SetAddress(0, 127, 0, 159);
    for (uint16_t counter = 0; counter < image.Size(); counter++) {
        SetPixel(image[counter]);
    }
}
void Tft::DrawRectangle(uint8_t hight, uint8_t width, uint8_t xAxis, uint8_t yAxis, TftColors color) {  //  NOLINT
    DrawHLine(xAxis, yAxis, width, color);
    DrawVLine(xAxis, yAxis, hight, color);
    DrawHLine(xAxis, yAxis + hight, width, color);
    DrawVLine(xAxis + width, yAxis, hight, color);
}
void Tft::SendCommand(uint8_t command) {
    Gpio::SetPinValue(config_.A0, Gpio::kLow);
    config_.TFtSpi.Write(command);
}
void Tft::SendData(uint8_t data) {
    Gpio::SetPinValue(config_.A0, Gpio::kHigh);
    config_.TFtSpi.Write(data);
}
void Tft::SetAddress(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY) {
    if ((startX < 127) && (startY < 159)) {
        //  Set X address
        SendCommand(kCASET);
        //  Start byte
        SendData(ExtractBits<uint16_t, 8>(startX));  // MS byte
        SendData(startX);  // LS byte
        //  Stop byte
        SendData(ExtractBits<uint16_t, 8>(endX));  // MS byte
        SendData(endX);  // LS byte
        //  Set Y address
        SendCommand(kRASET);
        //  Start byte
        SendData(ExtractBits<uint16_t, 8>(startY));  // MS byte
        SendData(startY);  // LS byte
        //  Stop byte
        SendData(ExtractBits<uint16_t, 8>(endY));  // MS byte
        SendData(endY);  // LS byte
        //  Memory write
        SendCommand(kRAWMR);    //  This tells the display that pixel data will follow.
    }
}
void Tft::SetPixel(uint16_t pixel) {
    //  write high byte
    SendData(ExtractBits<uint16_t, 8>(pixel));
    //  write low byte
    SendData(pixel & 0x00ff);
}
void Tft::DrawHLine(uint8_t xAxis, uint8_t yAxis, uint8_t length, TftColors color) {
    SetAddress(xAxis, xAxis + length -1, yAxis, yAxis);
    for (uint8_t counter = 0; counter < length; counter++) {
        SetPixel(color);
    }
}
void Tft::DrawVLine(uint8_t xAxis, uint8_t yAxis, uint8_t length, TftColors color) {
    SetAddress(xAxis, xAxis, yAxis, yAxis + length -1);
    for (uint8_t counter = 0; counter < length; counter++) {
        SetPixel(color);
    }
}

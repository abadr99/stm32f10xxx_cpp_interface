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
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "mcal/Rcc.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Spi.h"
#include "mcal/Systick.h"
#include "utils/Array.h"
#include "utils/Assert.h"
#include "hal/Tft.h"

using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::spi;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::systick;
using namespace stm32::type;
using namespace stm32::dev::hal::tft;


Tft::Tft(const TftConfig& config) : config_(config) {
    STM32_ASSERT(config_.A0.IsOutput(), CONFIG_ERROR(_TFT, _CONFIG));
    STM32_ASSERT(config_.rst.IsOutput(), CONFIG_ERROR(_TFT, _CONFIG));
    switch (config_.TFtSpi.GetSpiNum()) {
        case kSPI1: Rcc::Enable(Peripheral::kSPI1); break;
        case kSPI2: Rcc::Enable(Peripheral::kSPI2); break;
        default:break;
    }
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
void Tft::Reset() {
    Gpio::SetPinValue(config_.rst, kHigh);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(config_.rst, kLow);
    Systick::Delay_ms(2);
    Gpio::SetPinValue(config_.rst, kHigh);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(config_.rst, kLow);
    Systick::Delay_ms(100);
    Gpio::SetPinValue(config_.rst, kHigh);
    Systick::Delay_ms(120000);
}
void Tft::DisplayImage(const util::Array<uint16_t, 20480> image) {
    SetAddress(0, config_.width, 0, config_.height);
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
void Tft::SendCommand(uint8_t command) {
    Gpio::SetPinValue(config_.A0, kLow);
    config_.TFtSpi.Write(command);
}
void Tft::SendData(uint8_t data) {
    Gpio::SetPinValue(config_.A0, kHigh);
    config_.TFtSpi.Write(data);
}
void Tft::SetAddress(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY) {
    if ((startX < config_.width) && (startY < config_.height)) {
        //  Set X address
        SendCommand(kCASET);
        //  Start byte
        SendData(util::ExtractBits<uint16_t, 8>(startX));  // MS byte
        SendData(startX);   // LS byte
        //  Stop byte
        SendData(util::ExtractBits<uint16_t, 8>(endX));  // MS byte
        SendData(endX);  // LS byte
        //  Set Y address
        SendCommand(kRASET);
        //  Start byte
        SendData(util::ExtractBits<uint16_t, 8>(startY));  // MS byte
        SendData(startY);  // LS byte
        //  Stop byte
        SendData(util::ExtractBits<uint16_t, 8>(endY));  // MS byte
        SendData(endY);  // LS byte
        //  Memory write
        SendCommand(kRAWMR);    //  This tells the display that pixel data will follow.
    }
}
void Tft::SetPixel(uint16_t pixel) {
    //  write high byte
    SendData(util::ExtractBits<uint16_t, 8>(pixel));
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

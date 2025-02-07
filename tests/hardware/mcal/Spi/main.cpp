/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-09-22
 * @copyright Copyright (c) 2024
 */

// commit-id: 378ed655b5955066ea5865dd1badc756c439fcde

#include <stdint.h>
#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Spi.h"
#include "mcal/Systick.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::spi;
using namespace stm32::dev::mcal::systick;

int main(void) {
    Rcc::Init();
    Gpio::Init();
    Systick::Init();
    
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPA);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kSPI1);

    uint8_t txData = 0xAA;
    Pin SCK(kPortA, kPin5, PinMode::kAlternativePushPull_2MHz);
    Pin MOSI(kPortA, kPin7, PinMode::kAlternativePushPull_2MHz);
    Pin MISO(kPortA, kPin6, PinMode::kInputFloat);
    Pin SS(kPortA, kPin4, PinMode::kAlternativePushPull_2MHz);
    Pin led(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);


    Systick::Enable(kAHB_Div_8);
    SpiConfig spi1_config = {kSPI1, kSpi_8bit, kLSB, kMode0
                             , kSW, kF_DIV_8};
    Spi spi1(spi1_config);
    Gpio::Set(SCK);
    Gpio::Set(MOSI);
    Gpio::Set(MISO);
    Gpio::Set(SS);
    Gpio::Set(led);
    Gpio::SetPinValue(led, kHigh);

    spi1.MasterInit();
    spi1.Write(txData);

    uint8_t rxData = 0;
    rxData = spi1.Read();
    if (rxData == 0xAA) {
        Gpio::SetPinValue(led, kLow);
    } else {
        Gpio::SetPinValue(led, kHigh);
    }
    while (1) {
    }
}

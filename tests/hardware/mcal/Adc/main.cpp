/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * @copyright Copyright (c) 2024
 */

// commit-id: 5b79a736a1b30aa780301e71c922fae3514f65bf

#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "utils/Logger.h"
#include "mcal/Adc.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::mcal::adc;

int main() {
    Rcc::Init();
    Gpio::Init();
    
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPA);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kUSART1);
    Rcc::Enable(Peripheral::kADC1);

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Pin tx1(kPortA,  kPin9,  PinMode::kAlternativePushPull_10MHz);
    Gpio::Set(tx1);
    Gpio::Set(pc13);

    UsartConfig usart1_conf = {kUsart1, kRxTx, kSb_1_, kDataBits_8_, kNo_Parity,  kNone, 9600};
    Usart usart1(usart1_conf);
    usart1.Init();

    AdcConfig adc1_config = {kADC1, kLeft, kChannel16, kRegular, kSingle, kSoftware, kCycles_239_5};
    ADC adc1(adc1_config);
    adc1.Init();

    while (1) {
        uint16_t temp_value = adc1.GetTemperatureValue();
        if (temp_value > 15) {
            usart1.Transmit(temp_value);
            Gpio::SetPinValue(pc13, kLow);
        }
    }
}

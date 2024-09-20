/**
 * @file LM32.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "stm32f103xx.h"
#include "Rcc.h"
#include "Adc.h"
#include "LM35.h"

using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::adc;
using namespace stm32::dev::hal::lm35;

LM35::LM35(const adc_t& adc): adc_(adc) {
    switch (adc_.GetAdcNum()) {
        case kADC1: Rcc::Enable(Peripheral::kADC1); break;
        case kADC2: Rcc::Enable(Peripheral::kADC2); break;
        default: break;
    }
    adc_.Init();
}
uint16_t LM35::GetTempVal() {
    uint16_t result = adc_.StartSingleConversion();
    uint16_t TempVal = (result * 5000 / 4096);
    return (TempVal / 10);
}

/**
 * @file LDR.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mcal/inc/stm32f103xx.h"
#include "Rcc.h"
#include "Adc.h"
#include "LDR.h"

using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::adc;
using namespace stm32::dev::hal::ldr;

LDR::LDR(const adc_t& adc): adc_(adc) {
    switch (adc_.GetAdcNum()) {
        case kADC1: Rcc::Enable(Peripheral::kADC1); break;
        case kADC2: Rcc::Enable(Peripheral::kADC2); break;
        default: break;
    }
    adc_.Init();
}
uint16_t LDR::GetValue() {
    uint16_t result = adc_.StartSingleConversion();
    uint16_t DigtalVal = (5 * result) / 4096;
    return ((DigtalVal * 1000) / (5 - DigtalVal));
}

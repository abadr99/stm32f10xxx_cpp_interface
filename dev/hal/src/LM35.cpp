/**
 * @file LM32.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Adc.h"
#include "LM35.h"

using namespace stm32::dev::mcal::adc;
using namespace stm32::dev::hal::lm35;

template <AdcPeripheral P>
LM35<P>::LM35(const adc_t& adc): adc_(adc) { }

template <AdcPeripheral P>
void LM35<P>::Init() {
    adc_.Init();
}
template <AdcPeripheral P>
uint16_t LM35<P>::GetTempVal() {
    uint16_t result = adc_.startSingleConversion();
    uint16_t analogVal = static_cast<uint16_t>(static_cast<uint32_t>(result * 5000 / 4096));
    return (analogVal / 10);
}

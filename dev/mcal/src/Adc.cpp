/**
 * @file Adc.cpp
 * @brief 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Adc.h"

using namespace stm32::utils::bit_manipulation;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::adc;
using namespace stm32::registers::adc;

template<AdcPeripheral  ADC_NUM>
ADC<ADC_NUM>::ADC(const ADCConfig& config) : config_(config) {
        switch (ADC_NUM) {
        case kADC1 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>(ADC1)); break;
        case kADC2 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>(ADC2)); break;
        default: break;
    }
}
template<AdcPeripheral  ADC_NUM>
void ADC<ADC_NUM>::init() {
    ADC_reg->CR2.ADON = 0;  // Reset ADC
    ADC_reg->CR2.ALIGN = static_cast<uint32_t>(config_.alignment);
    ADC_reg->CR2.ADON = 1;
}
template<AdcPeripheral  ADC_NUM>
uint16_t ADC<ADC_NUM>:: startSingleConversion() {
        // Ensure ADC is not busy
        while (ADC_reg->SR.STRT) {
        }
        // Set up for single conversion
        ADC_reg->CR2.CONT = 0;  // Disable continuous mode
        ADC_reg->SQR1.L = 0;    // Set sequence length to 1
        ADC_reg->SQR3 = static_cast<uint8_t>(config_.channel);  // Set channel

        // Start conversion
        ADC_reg->CR2.SWSTART = 1;

        // Wait for conversion to complete
        while (!ADC_reg->SR.EOC) {
        }
        // Read and return the result
        return ADC_reg->DR.DATA;
    }
template<AdcPeripheral  ADC_NUM>
void ADC<ADC_NUM>::startContinuousConversion() {
        // Ensure ADC is not busy
        while (ADC_reg->SR.STRT);

        // Set up for continuous conversion
        ADC_reg->CR2.CONT = 1;  // Enable continuous mode
        ADC_reg->SQR1.L = 0;    // Set sequence length to 1
        ADC_reg->SQR3 = static_cast<uint8_t>(config_.channel);  // Set channel

        // Start conversion
        ADC_reg->CR2.SWSTART = 1;
}
template<AdcPeripheral  ADC_NUM>
uint16_t ADC<ADC_NUM>::readContinuousConversion() {
        // Wait for conversion to complete
        while (!ADC_reg->SR.EOC);

        // Read and return the result
        return ADC_reg->DR.DATA;
}
template<AdcPeripheral  ADC_NUM>
void ADC<ADC_NUM>::stopContinuousConversion() {
        ADC_reg->CR2.CONT = 0;  // Disable continuous mode
        ADC_reg->CR2.SWSTART = 0;  // Stop conversion
    }
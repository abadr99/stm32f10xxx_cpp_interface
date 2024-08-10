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
#include "mcal/inc/Rcc.h"
#include "mcal/inc/Adc.h"

using namespace stm32::utils::bit_manipulation;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::adc;
using namespace stm32::registers::adc;


ADC::ADC(const ADCConfig& config) : config_(config) {
    switch (config_.number) {
        case kADC1 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>(ADC1));
                     break;
        case kADC2 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>(ADC2));
                     break;
        default    : break;
    }
}

void ADC::init() {
    ADC_reg->CR2.registerVal = 0;  // Reset ADC
    ADC_reg->CR2.ALIGN = static_cast<RegWidth_t>(config_.alignment);
    if (config_.trigSource != kSOFTWARE) {
        if (config_.mode == kINJECTED) {
            ADC_reg->CR2.JEXTTRIG = 1;
            ADC_reg->CR2.JEXTSEL = static_cast<RegWidth_t>(config_.trigSource);
        } else {
            ADC_reg->CR2.EXTTRIG = 1;
            ADC_reg->CR2.EXTSEL = static_cast<RegWidth_t>(config_.trigSource);
        }
    }
    ADC_reg->CR2.ADON = 1;
}

uint16_t ADC:: startSingleConversion() {
    // Ensure ADC is not busy
    uint32_t ctr = 0;
    while ((ADC_reg->SR.STRT) && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    ctr = 0;
    // Set up for single conversion
    ADC_reg->CR2.CONT = 0;  // Disable continuous mode
    ADC_reg->SQR1.L = 0;    // Set sequence length to 1
    ADC_reg->SQR3 = static_cast<uint8_t>(config_.channel);  // Set channel
    configureChannelSample();
    // Start conversion
    ADC_reg->CR2.SWSTART = 1;
    // Wait for conversion to complete
    while (!ADC_reg->SR.EOC && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    // Read and return the result
    return ADC_reg->DR.DATA;
    }

void ADC::startContinuousConversion() {
    // Ensure ADC is not busy
    uint32_t ctr = 0;
    while (ADC_reg->SR.STRT  && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    // Set up for continuous conversion
    ADC_reg->CR2.CONT = 1;  // Enable continuous mode
    ADC_reg->SQR1.L = 0;    // Set sequence length to 1
    ADC_reg->SQR3 = static_cast<uint8_t>(config_.channel);  // Set channel
    configureChannelSample();
    // Start conversion
    ADC_reg->CR2.SWSTART = 1;
}

uint16_t ADC::readContinuousConversion() {
    uint32_t ctr = 0;
    // Wait for conversion to complete
    while (!ADC_reg->SR.EOC && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    // Read and return the result
    return ADC_reg->DR.DATA;
}

void ADC::stopContinuousConversion() {
    ADC_reg->CR2.CONT = 0;  // Disable continuous mode
    ADC_reg->CR2.SWSTART = 0;  // Stop conversion
}

uint16_t ADC::startInjectedConversion() {
    ADC_reg->JSQR.JL = 0;
    // Configure injected channel
    ADC_reg->JSQR.JSQ4 = static_cast<RegWidth_t>(config_.channel);
    configureChannelSample();
    // Start injected conversion
    ADC_reg->CR2.JSWSTART = 1;
    uint32_t ctr = 0;
    while ((!ADC_reg->SR.JEOC)&& (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    return ADC_reg->JDR1.registerVal;
}

void ADC::EnableInterrupt() {
    switch (config_.mode) {
    case kSINGLE:
        ADC_reg->CR1.EOCIE = 1;
        break;
    case kINJECTED:
        ADC_reg->CR1.JEOCIE = 1;
        break;
    default:
        break;
    }
}

void ADC::DisableInterrupt() {
    switch (config_.mode) {
    case kSINGLE:
        ADC_reg->CR1.EOCIE = 0;
        break;
    case kINJECTED:
        ADC_reg->CR1.JEOCIE = 0;
        break;
    default:
        break;
    }
}

void ADC::Disable() {
     ADC_reg->CR2.ADON = 0;
}

void ADC::configureChannelSample() { 
     // Configure sample time for the selected channel 
    RegWidth_t sampleTimeBits = static_cast<RegWidth_t>(config_.sampleTime);
    RegWidth_t channel = static_cast<uint32_t>(config_.channel);
    if (channel <= 9) { 
        ADC_reg->SMPR2.registerVal &= ~(0x7 << (3 * channel)); 
        ADC_reg->SMPR2.registerVal |= (sampleTimeBits << (3 * channel)); 
    } else { 
        uint32_t adjustedChannel = channel - 10; 
        ADC_reg->SMPR1.registerVal &= ~(0x7 << (3 * adjustedChannel)); 
        ADC_reg->SMPR1.registerVal |= (sampleTimeBits << (3 * adjustedChannel)); 
    } 
} 


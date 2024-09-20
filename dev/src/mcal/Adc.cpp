/**
 * @file Adc.cpp
 * @brief 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "utils/BitManipulation.h"
#include "mcal/Rcc.h"
#include "mcal/Adc.h"

using namespace stm32::util;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::adc;
using namespace stm32::registers::adc;

ASSERT_STRUCT_SIZE(ADCRegDef, (sizeof(RegWidth_t) * 20));

ASSERT_MEMBER_OFFSET(ADCRegDef, SR,          0);
ASSERT_MEMBER_OFFSET(ADCRegDef, CR1,          sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(ADCRegDef, CR2,         sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(ADCRegDef, SMPR1,         sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(ADCRegDef, SMPR2,         sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(ADCRegDef, JOFR1,         sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(ADCRegDef, JOFR2,        sizeof(RegWidth_t) * 6);
ASSERT_MEMBER_OFFSET(ADCRegDef, JOFR3,        sizeof(RegWidth_t) * 7);
ASSERT_MEMBER_OFFSET(ADCRegDef, JOFR4,        sizeof(RegWidth_t) * 8);
ASSERT_MEMBER_OFFSET(ADCRegDef, HTR,        sizeof(RegWidth_t) * 9);
ASSERT_MEMBER_OFFSET(ADCRegDef, LTR,        sizeof(RegWidth_t) * 10);
ASSERT_MEMBER_OFFSET(ADCRegDef, SQR1,        sizeof(RegWidth_t) * 11);
ASSERT_MEMBER_OFFSET(ADCRegDef, SQR2,        sizeof(RegWidth_t) * 12);
ASSERT_MEMBER_OFFSET(ADCRegDef, SQR3,        sizeof(RegWidth_t) * 13);
ASSERT_MEMBER_OFFSET(ADCRegDef, JSQR,        sizeof(RegWidth_t) * 14);
ASSERT_MEMBER_OFFSET(ADCRegDef, JDR1,        sizeof(RegWidth_t) * 15);
ASSERT_MEMBER_OFFSET(ADCRegDef, JDR2,        sizeof(RegWidth_t) * 16);
ASSERT_MEMBER_OFFSET(ADCRegDef, JDR3,        sizeof(RegWidth_t) * 17);
ASSERT_MEMBER_OFFSET(ADCRegDef, JDR4,        sizeof(RegWidth_t) * 18);
ASSERT_MEMBER_OFFSET(ADCRegDef, DR,        sizeof(RegWidth_t) * 19);

ADC::ADC(const AdcConfig& config) : config_(config) {
    switch (config_.number) {
        case kADC1 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>(ADC1));
                     break;
        case kADC2 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>(ADC2));
                     break;
        default    : break;
    }
}

void ADC::Init() {
    ADC_reg->CR2.registerVal = 0;  // Reset ADC
    ADC_reg->CR2.ALIGN = static_cast<RegWidth_t>(config_.alignment);
    if (config_.trigSource != kSoftware) {
        ADC_reg->CR2.ADON = 1;
        return;
    } else if (config_.mode == kSingleInjected) {
        ADC_reg->CR2.JEXTTRIG = 1;
        ADC_reg->CR2.JEXTSEL = static_cast<RegWidth_t>(config_.trigSource);
    } else {
        ADC_reg->CR2.EXTTRIG = 1;
        ADC_reg->CR2.EXTSEL = static_cast<RegWidth_t>(config_.trigSource);
    }
    ADC_reg->CR2.ADON = 1;
}

uint16_t ADC:: StartSingleConversion() {
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
    ConfigureChannelSample();
    // Start conversion
    ADC_reg->CR2.SWSTART = 1;
    // Wait for conversion to complete
    while (!ADC_reg->SR.EOC && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    // Read and return the result
    return ADC_reg->DR.DATA;
    }

void ADC::StartContinuousConversion() {
    // Ensure ADC is not busy
    uint32_t ctr = 0;
    while (ADC_reg->SR.STRT  && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    // Set up for continuous conversion
    ADC_reg->CR2.CONT = 1;  // Enable continuous mode
    ADC_reg->SQR1.L = 0;    // Set sequence length to 1
    ADC_reg->SQR3 = static_cast<uint8_t>(config_.channel);  // Set channel
    ConfigureChannelSample();
    // Start conversion
    ADC_reg->CR2.SWSTART = 1;
}

uint16_t ADC::ReadContinuousConversion() {
    uint32_t ctr = 0;
    // Wait for conversion to complete
    while (!ADC_reg->SR.EOC && (ctr != ADC_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != ADC_TIMEOUT);
    // Read and return the result
    return ADC_reg->DR.DATA;
}

void ADC::StopContinuousConversion() {
    ADC_reg->CR2.CONT = 0;  // Disable continuous mode
    ADC_reg->CR2.SWSTART = 0;  // Stop conversion
}

uint16_t ADC::StartInjectedConversion() {
    ADC_reg->JSQR.JL = 0;
    // Configure injected channel
    ADC_reg->JSQR.JSQ4 = static_cast<RegWidth_t>(config_.channel);
    ConfigureChannelSample();
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
    case kSingleRegular:
        ADC_reg->CR1.EOCIE = 1;
        break;
    case kSingleInjected:
        ADC_reg->CR1.JEOCIE = 1;
        break;
    default:
        break;
    }
}

void ADC::DisableInterrupt() {
    switch (config_.mode) {
    case kSingleRegular:
        ADC_reg->CR1.EOCIE = 0;
        break;
    case kSingleInjected:
        ADC_reg->CR1.JEOCIE = 0;
        break;
    default:
        break;
    }
}

void ADC::Disable() {
     ADC_reg->CR2.ADON = 0;
}

void ADC::ConfigureChannelSample() { 
     // Configure sample time for the selected channel 
    RegWidth_t sampleTimeBits = static_cast<RegWidth_t>(config_.sampleTime);
    RegWidth_t channel = static_cast<uint32_t>(config_.channel);
    if (channel <= 9) { 
        // Clear the bits
      ADC_reg->SMPR2.registerVal = ClearBits<uint32_t> (ADC_reg->SMPR2.registerVal,
                                                        3 * channel, 3 * channel + 2);
      ADC_reg->SMPR2.registerVal = WriteBits<uint32_t> (3 * channel, 3 * channel + 2,
                                                        ADC_reg->SMPR2.registerVal, sampleTimeBits);
    } else { 
      uint32_t adjustedChannel = channel - 10; 
      ADC_reg->SMPR1.registerVal = ClearBits<uint32_t> (ADC_reg->SMPR1.registerVal,
                                                        3 * adjustedChannel, 3 * adjustedChannel + 2);   //  NOLINT
      ADC_reg->SMPR1.registerVal = WriteBits<uint32_t> (3 * adjustedChannel, 3 * adjustedChannel + 2,   //  NOLINT
                                                        ADC_reg->SMPR1.registerVal, sampleTimeBits);
    } 
}
AdcNum ADC::GetAdcNum() {
    return config_.number;
}

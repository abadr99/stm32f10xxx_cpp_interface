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
using namespace stm32::type;
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

#define TO_STRING(str_)  #str_

#define ADC_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Adc error_)

#define CHECK_ADC_CONFIG() \
    STM32_ASSERT((config_.number >= kADC1) && (config_.number <= kADC2), \
                  ADC_CONFIG_ERROR(Number)); \
    STM32_ASSERT((config_.alignment == kRight) || (config_.alignment == kLeft), \
                  ADC_CONFIG_ERROR(Alignment)); \
    STM32_ASSERT((config_.channel >= kChannel0) && (config_.channel <= kChannel17), \
                  ADC_CONFIG_ERROR(Channel)); \
    STM32_ASSERT((config_.sampleTime >= kCycles_1_5) && (config_.sampleTime <=  kCycles_239_5), \
                  ADC_CONFIG_ERROR(Sample Time));

ADC::ADC(const AdcConfig& config) : config_(config) {
    switch (config_.number) {
        case kADC1 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>
                                (Addr<Peripheral::kADC1 >::Get()));
                     break;
        case kADC2 : ADC_reg = (reinterpret_cast<volatile ADCRegDef*>
                                (Addr<Peripheral::kADC2 >::Get()));
                     break;
        default    : break;
    }
}

void ADC::Init() {
    //  Reset ADC configuration 
    ADC_reg->CR1.registerVal = 0;
    ADC_reg->CR2.registerVal = 0;

    //  Wakes up the ADC from Power Down state
    ADC_reg->CR2.ADON = 1;

    //  Configure Alignment 
    ADC_reg->CR2.ALIGN = static_cast<RegWidth_t>(config_.alignment);

    //  Configure Mode
    switch (config_.mode) {
        case AdcMode::kSingle:
            ADC_reg->CR2.CONT = 0;   // Disable Continuous Mode
            ADC_reg->CR1.SCAN = 0;   // Disable Scan Mode
            break;
        case AdcMode::kContinuous:
            ADC_reg->CR2.CONT = 1;   // Enable Continuous Mode
            ADC_reg->CR1.SCAN = 0;   // Disable Scan Mode
            break;
        case AdcMode::kScanMode:
            ADC_reg->CR2.CONT = 0;   // Disable Continuous Mode
            ADC_reg->CR1.SCAN = 1;   // Enable Scan Mode
            break;
        case AdcMode::kDiscontinuous:
            ADC_reg->CR2.CONT = 0;   // Disable Continuous Mode
            ADC_reg->CR1.SCAN = 1;   // Enable Scan Mode
            break;
    }

    //  Configure Trigger Source
    if (config_.channelMode == AdcChannelMode::kRegular) {
        ADC_reg->CR2.EXTSEL = static_cast<RegWidth_t>(config_.trigSource);
    } else if (config_.channelMode == AdcChannelMode::kInjected) {
        ADC_reg->CR2.JEXTSEL = static_cast<RegWidth_t>(config_.trigSource);
    }

    if (config_.trigSource == AdcTriggerSource::kEXTI_LINE11) {
        ADC_reg->CR2.EXTTRIG = 1;   // Enable External conversion
    }
        
    //  Configure Channel Sequence
    if (config_.mode == AdcMode::kSingle) {
        if (config_.channelMode == kRegular) {
            ADC_reg->SQR1.L = 1;  // Only one channel
            ADC_reg->SQR3.SQ1 = static_cast<RegWidth_t>(config_.channel);
        } else if (config_.channelMode == kInjected) {
            ADC_reg->JSQR.JL = 1;  // Only one channel
            ADC_reg->JSQR.JSQ1 = static_cast<RegWidth_t>(config_.channel);
        }
    } else {
        // TODO(@nuran) : if needed
    }

    //  Configure Sampling cycles
    ConfigureChannelSample();
}

uint16_t ADC:: StartSingleConversion() {
    // Start COnversion
    ADC_reg->CR2.ADON = 1;

    // Ensure ADC is not busy
    util::BusyWait<constant::TimeOut::kAdc>([&](){ return !(ADC_reg->SR.STRT); });
    
    ConfigureChannelSample();
    // Start conversion of regular channel
    ADC_reg->CR2.SWSTART = 1;
    // Wait for conversion to complete
    util::BusyWait<constant::TimeOut::kAdc>([&](){ return !(ADC_reg->SR.EOC); });
    // Read and return the result
    return ADC_reg->DR.DATA;
}

uint16_t ADC:: GetTemperatureValue() {
    //  Enable Temperature Sensor
    ADC_reg->CR2.TSVREFE = 1;
    
    //  Get Adc Digital value
    uint16_t adc_value = StartSingleConversion();

    //  Convert the digital value to analog value(Voltage)
    float voltage_sense = (adc_value * (kVref / kAdcResolution));

    //  Convert the Voltage to a temperature value
    uint16_t temperature_value = ((kV25 - voltage_sense) / kAvgSlope) + kTempConstant; 
    return temperature_value;
}

void ADC::StartContinuousConversion() {
    // Ensure ADC is not busy
    util::BusyWait<constant::TimeOut::kAdc>([&](){ return !ADC_reg->SR.STRT; });
    
    // Start conversion
    ADC_reg->CR2.SWSTART = 1;
}

uint16_t ADC::ReadContinuousConversion() {
    // Wait for conversion to complete
    util::BusyWait<constant::TimeOut::kAdc>([&](){ return ADC_reg->SR.EOC; });
    // Read and return the result
    return ADC_reg->DR.DATA;
}

void ADC::StopContinuousConversion() {
    ADC_reg->CR2.CONT = 0;  // Disable continuous mode
    ADC_reg->CR2.SWSTART = 0;  // Stop conversion
}


void ADC::EnableInterrupt() {
    switch (config_.channelMode) {
    case kRegular:
        ADC_reg->CR1.EOCIE = 1;
        break;
    case kInjected:
        ADC_reg->CR1.JEOCIE = 1;
        break;
    default:
        break;
    }
}

void ADC::DisableInterrupt() {
    switch (config_.channelMode) {
    case kRegular:
        ADC_reg->CR1.EOCIE = 0;
        break;
    case kInjected:
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

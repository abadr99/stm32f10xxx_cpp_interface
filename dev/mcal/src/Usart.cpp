/**
 * @file Usart.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "stm32f103xx.h"
#include "Assert.h"
#include "Usart.h"

using namespace stm32::registers::rcc;
using namespace stm32::registers::usart;
using namespace stm32::dev::mcal::usart;

#define CHECK_CONFIG()\
    STM32_ASSERT((config_.mode >= kRx) && (config_.mode <= kRxTx));\
    STM32_ASSERT((config_.numOfSB >= kSb_1_) && (config_.numOfSB <= kSb_1_5_));\
    STM32_ASSERT((config_.dataBits == kDataBits_8_) || (config_.dataBits == kDataBits_9_));\
    STM32_ASSERT((config_.parityMode >= kNo_Parity) && (config_.parityMode <= kOdd_Parity));\
    STM32_ASSERT((config_.flowControlState >= kNone) && (config_.flowControlState <= kRTS_CTS));


ASSERT_STRUCT_SIZE(UsartRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(UsartRegDef, SR,          0);
ASSERT_MEMBER_OFFSET(UsartRegDef, DR,          sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(UsartRegDef, BRR,         sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR1,         sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR2,         sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR3,         sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(UsartRegDef, GTPR,        sizeof(RegWidth_t) * 6);

Usart::Usart(const UsartConfig& config) : config_(config) {
    switch (config_.number) {
        case kUsart1 : usartReg = (reinterpret_cast<volatile UsartRegDef*>(USART1)); break;
        case kUsart2 : usartReg = (reinterpret_cast<volatile UsartRegDef*>(USART2)); break;
        case kUsart3 : usartReg = (reinterpret_cast<volatile UsartRegDef*>(USART3)); break;
        default: break;
    }
}

void Usart::EnableClk() {
    switch (config_.number) {
        case kUsart1 : RCC->APB2ENR.USART1EN = Flag::kEnabled; break;
        case kUsart2 : RCC->APB1ENR.USART2EN = Flag::kEnabled; break;
        case kUsart3 : RCC->APB1ENR.USART3EN = Flag::kEnabled; break;
        default: break;
    }
}

void Usart::Init() {
    CHECK_CONFIG();
    /* Enable usart peripheral */
    usartReg->CR1.UE = kEnabled;
    /* Set mode */
    usartReg->CR1.RE_TE = config_.mode;
    /* Set stop bits*/
    usartReg->CR2.STOP = config_.numOfSB;
    /* Set data bits */
    usartReg->CR1.M = config_.dataBits;  
    /* Set parity mode */
    usartReg->CR1.PS_PCE = config_.parityMode;
    /* Set hardware flow control */
    usartReg->CR3.RTSE_CTSE = config_.flowControlState;
    
    _SetBaudRate();
}

void Usart::_SetBaudRate() {
    const uint32_t clockFrequency = 8000000;  // 8 MHz
    const uint32_t scale = 16;

    // Calculate the USARTDIV value
    float UsartDiv = ((clockFrequency) / (scale * config_.baudRate));

    // Extract the mantissa and fraction parts
    uint16_t divMantissa  = (uint16_t)UsartDiv;
    float fractionPart = (UsartDiv - divMantissa);

    // Calculate the fraction
    uint8_t divFraction = (uint16_t)(fractionPart * scale);
    
    // Assign the calculated values to the BRR register
    usartReg->BRR.DIV_Mantissa = divMantissa;
    usartReg->BRR.DIV_Fraction = divFraction;
}

void Usart::Transmit(DataValType dataValue) {
    uint32_t count = 0;
    while (!(usartReg->SR.TXE) ) {}
    STM32_ASSERT(count != USART_TIMEOUT && (count != USART_TIMEOUT) && (++count));
    count = 0;
    usartReg->DR = dataValue;
    while (!(usartReg->SR.TC)) {}
    STM32_ASSERT(count != USART_TIMEOUT && (count != USART_TIMEOUT) && (++count));
    usartReg->SR.registerVal = 0;
}

typename Usart::DataValType Usart::Receive() {
    uint32_t count = 0;
    while (!(usartReg->SR.RXNE) && (count != USART_TIMEOUT) && (++count) ) {}
    STM32_ASSERT(count != USART_TIMEOUT);
    return static_cast<DataValType>(usartReg->DR);
}

ErrorType Usart::RetErrorDetection() {
    if (usartReg->SR.PE == Flag::kEnabled) {
        return kParityError;
    } 
    if (usartReg->SR.FE == Flag::kEnabled) {
        return kFrameError;
    } 
    if (usartReg->SR.NE == Flag::kEnabled) {
        return kNoiseError;
    } 
    if (usartReg->SR.ORE == Flag::kEnabled) {
        return kOverRunError;
    }
    return kSuccess;
}

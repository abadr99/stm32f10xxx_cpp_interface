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

#include "Assert.h"
#include "BaseAddress.h"
#include "mcal/inc/stm32f103xx.h"
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

template<uint32_t USART_ADDRESS>
Usart<USART_ADDRESS>::Usart(const UsartConfig& config) : config_(config) {}

template<uint32_t USART_ADDRESS>
void Usart<USART_ADDRESS>::EnableClk() {
    switch (USART_ADDRESS) {
        case USART1 : RCC->APB2ENR.USART1EN = Flag::kEnabled; break;
        case USART2 : RCC->APB1ENR.USART2EN = Flag::kEnabled; break;
        case USART3 : RCC->APB1ENR.USART3EN = Flag::kEnabled; break;
        default: break;
    }
}

template<uint32_t USART_ADDRESS>
void Usart<USART_ADDRESS>::Init() {
    auto SetBaudRate = [&]() {
        const uint32_t clockFrequency = 8000000;  // 8 MHz
        const uint32_t scale = 16;
        const uint32_t multiplier = 1000;
        const uint32_t roundingFactor = 500;

        // Calculate the USARTDIV value
        uint32_t UsartDiv = ((clockFrequency * multiplier) / (scale * config_.baudRate));

        // Extract the mantissa and fraction parts
        uint16_t divMantissa  = UsartDiv / multiplier;
        uint16_t fractionPart = UsartDiv % multiplier;

        // Calculate the fraction
        uint8_t divFraction = ((fractionPart * scale) + roundingFactor) / multiplier;

        // Assign the calculated values to the BRR register
        GET_USART_REG(USART_ADDRESS)->BRR.DIV_Mantissa = divMantissa;
        GET_USART_REG(USART_ADDRESS)->BRR.DIV_Fraction = divFraction;
    };

    CHECK_CONFIG();
    /* Enable usart peripheral */
    GET_USART_REG(USART_ADDRESS)->CR1.UE = kEnabled;
    /* Set mode */
    GET_USART_REG(USART_ADDRESS)->CR1.RE_TE = config_.mode;
    /* Set stop bits*/
    GET_USART_REG(USART_ADDRESS)->CR2.STOP = config_.numOfSB;
    /* Set data bits */
    GET_USART_REG(USART_ADDRESS)->CR1.M = config_.dataBits;  
    /* Set parity mode */
    GET_USART_REG(USART_ADDRESS)->CR1.PS_PCE = config_.parityMode;
    /* Set hardware flow control */
    GET_USART_REG(USART_ADDRESS)->CR3.RTSE_CTSE = config_.flowControlState;
    SetBaudRate();
}

template<uint32_t USART_ADDRESS>
void Usart<USART_ADDRESS>::Transmit(DataValType dataValue) {
    uint32_t count = 0;
    while (!(GET_USART_REG(USART_ADDRESS)->SR.TXE) && (count != USART_TIMEOUT) && (++count)) {}
    STM32_ASSERT(count != USART_TIMEOUT);
    count = 0;
    GET_USART_REG(USART_ADDRESS)->DR = dataValue; 
    while (!(GET_USART_REG(USART_ADDRESS)->SR.TC) && (count != USART_TIMEOUT) && (++count)) {}
    STM32_ASSERT(count != USART_TIMEOUT);
}

template<uint32_t USART_ADDRESS>
typename Usart<USART_ADDRESS>::DataValType Usart<USART_ADDRESS>::Receive() {
    uint32_t count = 0;
    while (!(GET_USART_REG(USART_ADDRESS)->SR.RXNE) && (count != USART_TIMEOUT) && (++count)) {}
    STM32_ASSERT(count != USART_TIMEOUT);
    return static_cast<DataValType>(GET_USART_REG(USART_ADDRESS)->DR);
}

template<uint32_t USART_ADDRESS>
ErrorType Usart<USART_ADDRESS>::RetErrorDetection() {
    if (GET_USART_REG(USART_ADDRESS)->SR.PE == Flag::kEnabled) {
        return kParityError;
    } 
    if (GET_USART_REG(USART_ADDRESS)->SR.FE == Flag::kEnabled) {
        return kFrameError;
    } 
    if (GET_USART_REG(USART_ADDRESS)->SR.NE == Flag::kEnabled) {
        return kNoiseError;
    } 
    if (GET_USART_REG(USART_ADDRESS)->SR.ORE == Flag::kEnabled) {
        return kOverRunError;
    }
    return kSuccess;
}

template class Usart<USART1>;
template class Usart<USART2>;
template class Usart<USART3>;

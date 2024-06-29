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
#include "../../mcal/inc/stm32f103xx.h"
#include "../../utils/inc/Assert.h"
#include "../../mcal/inc/Usart.h"
using namespace stm32::registers::rcc;
using namespace stm32::registers::usart;
using namespace stm32::dev::mcal::inc::usart;

ASSERT_STRUCT_SIZE(UsartRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(UsartRegDef, SR,         0);
ASSERT_MEMBER_OFFSET(UsartRegDef, DR,          sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(UsartRegDef, BRR,         sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR1,         sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR2,         sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR3,         sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(UsartRegDef, GTPR,        sizeof(RegWidth_t) * 6);

extern volatile UsartRegDef* USARTX[3];

void Usart::EnableClk(const UsartConfig& config) {
    STM32_ASSERT((config.usartNum >= kUsart1) && (config.usartNum <= kUsart3));
    switch (config.usartNum) {
        case kUsart1 : RCC->APB2ENR.USART1EN = kOn; break;
        case kUsart2 : RCC->APB1ENR.USART2EN = kOn; break;
        case kUsart3 : RCC->APB1ENR.USART3EN = kOn; break;
    }
}

void Usart::Init(const UsartConfig& config) {
    Usart::_Helper_CheckConfig(config);
    /* Enable usart peripheral */
    USARTX[config.usartNum]->CR1.UE = kOn;
    /* Set mode */
    USARTx[config.usartNum]->CR1.RE_TE = config.mode;
    /* Set stop bits*/
    USARTx[config.usartNum]->CR2.STOP = config.numOfSB;
    /* Set data bits */
    USARTx[config.usartNum]->CR1.M = config.dataBits;  
    /* Set parity mode */
    USARTx[config.usartNum]->CR1.PS_PCE = config.parityMode;
    /* Set hardware flow control */
    USARTX[config.usartNum]->CR3.RTSE_CTSE = config.flowControlState;
    Usart::_Helper_SetBaudRate(config);
}

void Usart::Transmit(const UsartConfig& config, uint16_t dataValue) {
    STM32_ASSERT((config.usartNum >= kUsart1) && (config.usartNum <= kUsart3));
    uint32_t count = 0;
    while (!(USARTx[config.usartNum]->SR.TXE) && (count != USART_TIMEOUT) && (++count)) {}
    STM32_ASSERT(count != USART_TIMEOUT);
    count = 0;
    USARTx[config.usartNum]->DR = dataValue; 
    while (!(USARTx[config.usartNum]->SR.TC) && (count != USART_TIMEOUT) && (++count)) {}
    STM32_ASSERT(count != USART_TIMEOUT);
}

uint16_t Usart::Receive(const UsartConfig& config) {
    STM32_ASSERT((config.usartNum >= kUsart1) && (config.usartNum <= kUsart3));
    uint32_t count = 0;
    while (!(USARTx[config.usartNum]->SR.RXNE) && (count != USART_TIMEOUT) && (++count)) {}
    STM32_ASSERT(count != USART_TIMEOUT);
    return static_cast<uint16_t>(USARTx[config.usartNum]->DR);
}

ErrorType Usart::RetErrorDetection(const UsartConfig& config) {
    STM32_ASSERT((config.usartNum >= kUsart1) && (config.usartNum <= kUsart3));
    ErrorType errorType;
    if (USARTx[config.usartNum]->SR.PE == kOn) {
        errorType = kParityError;
    } else if (USARTx[config.usartNum]->SR.FE == kOn) {
        errorType = kFrameError;
    } else if (USARTx[config.usartNum]->SR.NE == kOn) {
        errorType = kNoiseError;
    } else if (USARTx[config.usartNum]->SR.ORE == kOn) {
        errorType = kOverRunError;
    } else {
       errorType = kSuccess; 
    }
    return errorType;
}

void Usart::_Helper_SetBaudRate(const UsartConfig& config) {
    uint32_t USARTDIV;
    uint16_t divMantissa;
    uint8_t fractionPart;
    uint8_t divFraction;
    USARTDIV = ((8*1000000) / (16 * config.baudRate)) * 1000;
    divMantissa = USARTDIV / 1000;
    fractionPart = USARTDIV % 1000;
    divFraction = 16 * fractionPart;
    divFraction += 500;
    divFraction /= 1000;
    USARTX[config.usartNum]->BRR.DIV_Fraction = divFraction; 
    USARTX[config.usartNum]->BRR.DIV_Mantissa = divMantissa;
}

void Usart::_Helper_CheckConfig(const UsartConfig& config) {
    STM32_ASSERT((config.usartNum >= kUsart1) && (config.usartNum <= kUsart3));
    STM32_ASSERT((config.mode >= kRx) && (config.mode <= kRxTx));
    STM32_ASSERT((config.numOfSB >= kSb_1_) && (config.numOfSB <= kSb_1_5_));
    STM32_ASSERT((config.dataBits == kDataBits_8_) || (config.dataBits == kDataBits_9_));
    STM32_ASSERT((config.parityMode >= kNo_Parity) && (config.parityMode <= kOdd_Parity));
    STM32_ASSERT((config.flowControlState >= kNone) && (config.flowControlState <= kRTS_CTS));
}





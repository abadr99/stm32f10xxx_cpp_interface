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

#include "mcal/stm32f103xx.h"
#include "utils/Constant.h"
#include "utils/BitManipulation.h"
#include "utils/Util.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "mcal/Usart.h"

using namespace stm32::registers::rcc;
using namespace stm32::registers::usart;
using namespace stm32::dev::mcal::usart;
using namespace stm32::type;

#define TO_STRING(str_)  #str_

#define USART_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Usart error_)

#define RCC__TX_TIME_OUT_ERROR  "Timeout while waiting transmitting the data."
#define RCC__RX_TIME_OUT_ERROR  "Timeout while waiting receiving the data."

pFunction  Usart::pTransmitCompleteFun_[3] = {nullptr};
pFunction  Usart::pReceiveReadyFun_[3] = {nullptr};

volatile Usart::DataValType* Usart::pReceivedData_[3] = {nullptr, nullptr, nullptr};
stm32::type::RegType<UsartRegDef>::ptr Usart::usartReg = nullptr;

#define CHECK_CONFIG()\
    STM32_ASSERT((config_.mode >= kRx) && (config_.mode <= kRxTx), USART_CONFIG_ERROR(Mode));\
    STM32_ASSERT((config_.numOfSB >= kSb_1_) && (config_.numOfSB <= kSb_1_5_), \
    USART_CONFIG_ERROR(Stop Bit));\
    STM32_ASSERT((config_.dataBits == kDataBits_8_) || (config_.dataBits == kDataBits_9_), \
    USART_CONFIG_ERROR(Data Bits));\
    STM32_ASSERT((config_.parityMode >= kNo_Parity) && (config_.parityMode <= kOdd_Parity), \
    USART_CONFIG_ERROR(Parity Modes));\
    STM32_ASSERT((config_.flowControlState >= kNone) && (config_.flowControlState <= kRTS_CTS), \
    USART_CONFIG_ERROR(HW Flow Control));


ASSERT_STRUCT_SIZE(UsartRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(UsartRegDef, SR,          0);
ASSERT_MEMBER_OFFSET(UsartRegDef, DR,          sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(UsartRegDef, BRR,         sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR1,         sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR2,         sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR3,         sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(UsartRegDef, GTPR,        sizeof(RegWidth_t) * 6);


Usart::Usart(const UsartConfig& config)
: config_(config) {
    switch (config_.number) {
        case kUsart1 : usartReg = (reinterpret_cast<volatile UsartRegDef*>
                                   (Addr<Peripheral::kUSART1 >::Get())); break;
        case kUsart2 : usartReg = (reinterpret_cast<volatile UsartRegDef*>
                                   (Addr<Peripheral::kUSART2 >::Get())); break;
        case kUsart3 : usartReg = (reinterpret_cast<volatile UsartRegDef*>
                                   (Addr<Peripheral::kUSART3 >::Get())); break;
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
    float UsartDiv = (static_cast<float>(clockFrequency) / (scale * config_.baudRate));

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
    util::BusyWait<constant::TimeOut::kUsart>([&](){return !(usartReg->SR.TXE);});
    usartReg->DR = dataValue;
    util::BusyWait<constant::TimeOut::kUsart>([&](){return !(usartReg->SR.TC);});
    usartReg->SR.registerVal = 0;
}

void  Usart::Transmit(DataValType dataValue, pFunction pISR) {
    // Helper_SetTransmittedData(this->config_.number, dataValue);
    SetTransmitCompleteISR(this->config_.number, pISR);
    this->usartReg->DR = dataValue;
    //  Enable Transmit complete interrupt 
    this->usartReg->CR1.TCIE = 1;
}
typename Usart::DataValType Usart::Receive() {
    while (!(usartReg->SR.RXNE)){}
    return static_cast<DataValType>(usartReg->DR);
}

void Usart::Receive(DataValType* pData, pFunction pISR) {
    SetReceiveReadyISR(this->config_.number, pISR);
    pReceivedData_[static_cast<uint8_t>(this->config_.number)] = pData;
    //  Enable Receive interrupt 
    usartReg->CR1.RXNEIE = 1;
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

UsartNum Usart::GetUsartNum() {
    return config_.number;
}

void Usart::SetTransmitCompleteISR(UsartNum number, pFunction pISR) {
    pTransmitCompleteFun_[static_cast<uint8_t>(number)] = pISR;
}

void Usart::SetReceiveReadyISR(UsartNum number, pFunction pISR) {
    pReceiveReadyFun_[static_cast<uint8_t>(number)] = pISR;
}

pFunction Usart::Helper_GetTransmitCompleteISR(UsartNum number) {
    return pTransmitCompleteFun_[static_cast<uint8_t>(number)];
}

pFunction Usart::Helper_GetReceiveReadyISR(UsartNum number) {
    return pReceiveReadyFun_[static_cast<uint8_t>(number)];
}

void Usart::Helper_SetReceivedData(UsartNum number, DataValType data)  {
    *(Usart::pReceivedData_[static_cast<uint8_t>(number)]) = data;
}

extern "C" void USART1_IRQHandler(void) {
    pFunction func = nullptr;
    auto USART1 = (reinterpret_cast<volatile UsartRegDef*>
                  (Addr<Peripheral::kUSART1 >::Get()));
    // Check if the transmission is complete
    if (USART1->SR.TC == 1) {
        func = Usart::Helper_GetTransmitCompleteISR(kUsart1);
        if (func != NULL) {
            func();
        }
        // Clear the transmission complete flag
        USART1->SR.TC = 0;
    }
    // Check if data is received
    if (USART1->SR.RXNE == 1) {
        func = Usart::Helper_GetReceiveReadyISR(kUsart1);
        // Store the received data
        Usart::Helper_SetReceivedData(kUsart1, static_cast<Usart::DataValType>(USART1->DR));
        if (func != NULL) {
            func();
        }
        // Clear the receive flag
        USART1->SR.RXNE = 0;
    }
}

extern "C" void USART2_IRQHandler(void) {
    pFunction func = nullptr;
    auto USART2 = (reinterpret_cast<volatile UsartRegDef*>
                  (Addr<Peripheral::kUSART2 >::Get()));
    if (USART2->SR.TC == 1) {
        func = Usart::Helper_GetTransmitCompleteISR(kUsart2);
        if (func != NULL) {
            func();
        }
        USART2->SR.TC = 0;
    }
    if (USART2->SR.RXNE == 1) {
        Usart::Helper_SetReceivedData(kUsart2, static_cast<Usart::DataValType>(USART2->DR));
        func = Usart::Helper_GetReceiveReadyISR(kUsart2);
        if (func != NULL) {
            func();
        }
        USART2->SR.RXNE = 0;
    }
}

extern "C" void USART3_IRQHandler(void) {
    pFunction func = nullptr;
    auto USART3 = (reinterpret_cast<volatile UsartRegDef*>
                  (Addr<Peripheral::kUSART3 >::Get()));
    if (USART3->SR.TC == 1) {
        func = Usart::Helper_GetTransmitCompleteISR(kUsart3);
        if (func != NULL) {
            func();
        }
        USART3->SR.TC = 0;
    }
    if (USART3->SR.RXNE == 1) {
        Usart::Helper_SetReceivedData(kUsart3, static_cast<Usart::DataValType>(USART3->DR));
        func = Usart::Helper_GetReceiveReadyISR(kUsart3);
        if (func != NULL) {
            func();
        }
        USART3->SR.RXNE = 0;
    }
}

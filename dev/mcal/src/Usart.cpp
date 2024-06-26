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

#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Assert.h"
#include "mcal/inc/Usart.h"

using namespace stm32::dev::mcal::usart; // NOLINT[build/namespaces]
using namespace stm32::registers::usart; // NOLINT[build/namespaces]

ASSERT_STRUCT_SIZE(UsartRegDef, (sizeof(RegWidth_t) * 7));

ASSERT_MEMBER_OFFSET(UsartRegDef, SR,         0);
ASSERT_MEMBER_OFFSET(UsartRegDef, DR,          sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(UsartRegDef, BRR,         sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR1,         sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR2,         sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR3,         sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(UsartRegDef, GTPR,        sizeof(RegWidth_t) * 6);

void Usart::Init(uint32_t baudRate, uint8_t wordLength, uint8_t parity, uint8_t stopBits) {
    USART->BRR = baudRate;

    USART->CR1.M = wordLength;
    USART->CR1.PS = parity;

    USART->CR2.STOP = stopBits;

    USART->CR1.TE = 1;
    USART->CR1.RE = 1;
    USART->CR1.UE = 1;
}
void Usart::Transmit(uint8_t data) {
    USART->DR = data;
    while (USART->SR.TC == 0) {}
}
uint8_t Usart::Receive(uint32_t timeout) {
    uint16_t counter = 0;
    uint8_t receiveData = 0;
    while (USART->SR.RXNE == 0) {
        counter++;
        if (counter >= timeout) {
            receiveData = 255;
            break;
        }
    }
    if (counter < 255) {
        receiveData = USART->DR;
    }
    return receiveData;
}

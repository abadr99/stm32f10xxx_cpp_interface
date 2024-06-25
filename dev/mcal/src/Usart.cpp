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
ASSERT_MEMBER_OFFSET(UsartRegDef, CR[0],       sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR[1],       sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(UsartRegDef, CR[2],       sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(UsartRegDef, GTPR,        sizeof(RegWidth_t) * 6);

void Usart::Init(uint32_t baudRate, uint8_t wordLength, uint8_t parity, uint8_t stopBits) {
    USART->BRR = baudRate;

    USART->CR[0] = 0;
    USART->CR[0] |= (wordLength <<12);
    USART->CR[0] |= (parity <<9);

    USART->CR[1] = 0;
    USART->CR[1] |= (stopBits <<12);
}

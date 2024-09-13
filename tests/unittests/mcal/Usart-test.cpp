/**
 * @file Usart-test.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-09-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Usart.h"

uint32_t USART1Reg[7] ={};
uint32_t USART2Reg[7] ={};
uint32_t USART3Reg[7] ={};

using namespace stm32::util;
using namespace stm32::dev::mcal::usart;
using namespace stm32::registers::usart;

TEST(UsartTest, Init) {
    UsartConfig usartConfig = {kUsart1, kRx, kSb_1_, kDataBits_8_, kNo_Parity, kNone, 9600};
    Usart usart1(usartConfig);
    usart1.Init();
    EXPECT_EQ(1, (ExtractBit<uint32_t>(USART1->CR1.registerVal, 13)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 2, 3>(USART1->CR1.registerVal)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 12, 13>(USART1->CR2.registerVal)));
    EXPECT_EQ(0, (ExtractBit<uint32_t>(USART1->CR1.registerVal, 12)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 9, 10>(USART1->CR1.registerVal)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 8, 9>(USART1->CR3.registerVal)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 0, 3>(USART1->BRR.registerVal)));
    EXPECT_EQ(52, (ExtractBits<uint32_t, 4, 11>(USART1->BRR.registerVal)));
}

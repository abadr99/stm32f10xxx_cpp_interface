/**
 * @file Nvic-test.cpp
 * @author Manar
 * @version 0.1
 * @date 2024-06-23
 * @copyright Copyright (c) 2024
 */

#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Nvic.h"


uint32_t NvicReg[905] = {};
uint32_t ScbReg[18] = {};

using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::registers::nvic;

TEST(NvicTest, EnableInterrupt) {
    Nvic::EnableInterrupt(kEXTI0);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 6>(NVIC->ISER[0])));
    Nvic::EnableInterrupt(kUSART3);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 7>(NVIC->ISER[1])));
}
TEST(NvicTest, DisableInterrupt) {
    Nvic::DisableInterrupt(kEXTI0);
    EXPECT_EQ(0,   (ExtractBits<uint32_t, 6>(NVIC->ICER[0])));
    Nvic::DisableInterrupt(kUSART3);
    EXPECT_EQ(0,   (ExtractBits<uint32_t, 7>(NVIC->ICER[1])));
}
TEST(NvicTest, SetPendingFlag) {
    Nvic::SetPendingFlag(kEXTI0);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 6>(NVIC->ISPR[0])));
    Nvic::SetPendingFlag(kUSART3);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 7>(NVIC->ISPR[1])));
}
TEST(NvicTest, ClearPendingFlag) {
    Nvic::ClearPendingFlag(kEXTI0);
    EXPECT_EQ(0,   (ExtractBits<uint32_t, 6>(NVIC->ICPR[0])));
    Nvic::ClearPendingFlag(kUSART3);
    EXPECT_EQ(0,   (ExtractBits<uint32_t, 7>(NVIC->ICPR[1])));
}
TEST(NvicTest, SetPriority) {
    Nvic::SetPriority(kEXTI0, 5);
    EXPECT_EQ(5,   (ExtractBits<uint32_t, 4, 7>(NVIC->IPR[kEXTI0])));
    EXPECT_EQ(80,   (ExtractBits<uint32_t, 0, 7>(NVIC->IPR[kEXTI0])));
}
TEST(NvicTest, SetPriorityGroup) {
    Nvic::SetPriorityGroup(kSCB_0GROUP_4SUBGROUP);
    EXPECT_EQ(kSCB_0GROUP_4SUBGROUP,   (ExtractBits<uint32_t, 0, 31>(SCB->AIRCR)));
}

/**
 * @file BitManipulation-test.cpp

 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <gtest/gtest.h>

#include "utils/BitManipulation.h"

using namespace stm32::util;

TEST(BitManipulation, GetAllOnes) {
    EXPECT_EQ(0xFF,       (GetAllOnes<uint8_t>()));
    EXPECT_EQ(0xFFFF,     (GetAllOnes<uint16_t>()));
    EXPECT_EQ(0xFFFFFFFF, (GetAllOnes<uint32_t>()));
}

TEST(BitManipulation, GetOnes) {
    EXPECT_EQ(0,          (GetOnes<uint8_t>(0)));
    EXPECT_EQ(0b1,        (GetOnes<uint8_t>(1)));
    EXPECT_EQ(0b11,       (GetOnes<uint8_t>(2)));
    EXPECT_EQ(0b111,      (GetOnes<uint8_t>(3)));
    EXPECT_EQ(0b1,        (GetOnes<uint32_t>(1)));
    EXPECT_EQ(0b11,       (GetOnes<uint32_t>(2)));
    EXPECT_EQ(0b111,      (GetOnes<uint32_t>(3)));
    EXPECT_EQ(0x7FF,      (GetOnes<uint32_t>(11)));
    EXPECT_EQ(0xFFFFF,    (GetOnes<uint32_t>(20)));
    EXPECT_EQ(0xFFFFFFFF, (GetOnes<uint32_t>(32)));
}

TEST(BitManipulation, ExtractBits_startBit) {
    const uint32_t bits = 0xABCD1234;
    EXPECT_EQ(0, (ExtractBits<uint32_t, 0>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 1>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 2>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 3>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 4>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 8>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 9>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 10>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 11>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 15>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 16>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 17>(bits)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 20>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 22>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 25>(bits)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 31>(bits)));
}

TEST(BitManipulation, ExtractBits_startBit_endBit) {
    const uint32_t bits = 0xABCD1234;
    EXPECT_EQ(0x34,       (ExtractBits<uint32_t, 0, 7>(bits)));
    EXPECT_EQ(0x02,       (ExtractBits<uint32_t, 1, 3>(bits)));
    EXPECT_EQ(0x12,       (ExtractBits<uint32_t, 8, 15>(bits)));
    EXPECT_EQ(0x2F3448D,  (ExtractBits<uint32_t, 2, 27>(bits)));
    EXPECT_EQ(0xABCD1234, (ExtractBits<uint32_t, 0, 31>(bits)));
}
TEST(BitManipulation, ClearBits) {
    const uint8_t bits = 0b11111111;
    EXPECT_EQ(0b11111011, (ClearBits<uint8_t, 2>(bits)));
    EXPECT_EQ(0b01111111, (ClearBits<uint8_t, 7>(bits)));
    EXPECT_EQ(0b11000011, (ClearBits<uint8_t, 2, 5>(bits)));
    EXPECT_EQ(0b11000000, (ClearBits<uint8_t, 0, 5>(bits)));
    EXPECT_EQ(0b00000000, (ClearBits<uint8_t, 0, 7>(bits)));
}
TEST(BitManipulation, SetBits) {
    const uint8_t bits = 0b00000000;
    EXPECT_EQ(0b00000100, (SetBits<uint8_t, 2>(bits)));
    EXPECT_EQ(0b10000000, (SetBits<uint8_t, 7>(bits)));
    EXPECT_EQ(0b00111100, (SetBits<uint8_t, 2, 5>(bits)));
    EXPECT_EQ(0b00111111, (SetBits<uint8_t, 0, 5>(bits)));
    EXPECT_EQ(0b11111111, (SetBits<uint8_t, 0, 7>(bits)));
}

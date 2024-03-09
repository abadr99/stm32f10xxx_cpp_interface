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

#include "utils/inc/BitManipulation.h"


using namespace stm32::dev::utils::bit_manipulation;  // NOLINT [build/namespaces]

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

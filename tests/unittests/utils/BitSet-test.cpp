/**
 * @file BitSet-test.cpp
 * @brief
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdint.h>
#include <gtest/gtest.h>

#include "utils/inc/BitSet.h"

using stm32::utils::bitset::BitSet;

TEST(BitSet, BasicTest1) {
    BitSet<uint8_t> bs(0b11110000);

    bs.SetValue<0, 3>(0b1010);
    EXPECT_EQ((bs.GetValue<0, 3>()), 0b1010);
    EXPECT_EQ((bs.GetValue<4, 7>()), 0b1111);

    bs.SetValue<4, 7>(0);
    EXPECT_EQ((bs.GetValue<4, 7>()), 0);

    EXPECT_EQ((bs[5]), 0);
    EXPECT_EQ((bs[0]), 0);
    EXPECT_EQ((bs[1]), 1);
}

TEST(BitSet, Sizeof) {
    BitSet<uint8_t>  bs_8(0b11110000);
    BitSet<uint16_t> bs_16(0b11110000);
    BitSet<uint32_t> bs_32(0b11110000);
    BitSet<uint64_t> bs_64(0b11110000);
    EXPECT_EQ(sizeof(bs_8),  1);
    EXPECT_EQ(sizeof(bs_16), 2);
    EXPECT_EQ(sizeof(bs_32), 4);
    EXPECT_EQ(sizeof(bs_64), 8);
}

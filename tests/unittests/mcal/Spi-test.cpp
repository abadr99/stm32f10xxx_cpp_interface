/**
 * @file SPI-test.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-05-3
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Spi.h"

uint32_t SpiReg[9] = {0x0};
using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::spi;
using namespace stm32::registers::spi;

TEST(SPI, MasterInit) {
    SpiConfig spi = {.data = kSPI_8bit,
                     .frame = kMSB,
                     .clk = kMODE0,
                     .slave = kSW,
                     .br = kF_DIV_32};
    Spi<kSPI1> obj;
    obj.MasterInit(spi);
    //  test .data 
    EXPECT_EQ(0, (ExtractBits<uint32_t, 11>(SPI1->CR1.DFF)));
    //  test.frame
    EXPECT_EQ(0, (ExtractBits<uint32_t, 7>(SPI1->CR1.LSBFIRST)));
    // test .clk
    EXPECT_EQ(0, (ExtractBits<uint32_t, 0>(SPI1->CR1.CPHA)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 1>(SPI1->CR1.CPOL)));
    //  test .slave
    EXPECT_EQ(1, (ExtractBits<uint32_t, 9>(SPI1->CR1.SSM)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 8>(SPI1->CR1.SSI)));
    //  test .br
    EXPECT_EQ(4 , (ExtractBits<uint32_t, 3, 5>(SPI1->CR1.registerVal)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 2>(SPI1->CR1.MSTR)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 6>(SPI1->CR1.SPE)));
}
TEST(SPI, SlaveInit) {
    SpiConfig spi = {.data = kSPI_8bit,
                     .frame = kMSB,
                     .clk = kMODE0,
                     .slave = kSW,
                     .br = kF_DIV_32};
    Spi<kSPI1> obj;
    obj.MasterInit(spi);
    //  test .data 
    EXPECT_EQ(0, (ExtractBits<uint32_t, 11>(SPI1->CR1.DFF)));
    //  test.frame
    EXPECT_EQ(0, (ExtractBits<uint32_t, 7>(SPI1->CR1.LSBFIRST)));
    // test .clk
    EXPECT_EQ(0, (ExtractBits<uint32_t, 0>(SPI1->CR1.CPHA)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 1>(SPI1->CR1.CPOL)));
    //  test .slave
    EXPECT_EQ(1, (ExtractBits<uint32_t, 9>(SPI1->CR1.SSM)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 8>(SPI1->CR1.SSI)));
    //  test .br
    EXPECT_EQ(4 , (ExtractBits<uint32_t, 3, 5>(SPI1->CR1.registerVal)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 2>(SPI1->CR1.MSTR)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 6>(SPI1->CR1.SPE)));
}
TEST(SPI, Write) {
    uint8_t data = 'M';
    Spi<kSPI2> obj;
    obj.Write(data);
    EXPECT_EQ('M', (ExtractBits<uint32_t, 0, 15>(SPI1->DR)));
}
TEST(SPI, Read) {
    uint8_t data = 'A';
    Spi<kSPI2> obj;
    obj.Write(data);
    EXPECT_EQ('A', obj.Read());
}

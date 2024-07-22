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
    SpiConfig spi={.data = kSPI_8bit,
                    .frame = kMSB,
                    .clk = kMODE0,
                    .slave = kSW,
                    .br = kF_DIV_32};
    Spi<kSPI1> obj;
    obj.MasterInit(spi);
    EXPECT_EQ(4 , (ExtractBits<uint32_t, 3, 5>(SPI1->CR1.registerVal)));
}

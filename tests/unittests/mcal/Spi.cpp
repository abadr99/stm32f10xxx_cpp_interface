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
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Spi.h"

uint32_t SpiReg[8] = {0x0};
using namespace stm32::util;
using namespace stm32::dev::mcal::spi;
using namespace stm32::registers::spi;

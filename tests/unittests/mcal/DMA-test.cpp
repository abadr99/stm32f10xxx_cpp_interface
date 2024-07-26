/**
 * @file DMA.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/DMA.h"

using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::dma;
using namespace stm32::registers::dma;
using namespace stm32::registers::gpio;

uint32_t DmaReg[30] = {0x0};

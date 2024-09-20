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
#include "BitManipulation.h"
#include "stm32f103xx.h"
#include "Pin.h"
#include "Dma.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::dma;
using namespace stm32::registers::dma;
using namespace stm32::registers::gpio;

uint32_t DmaReg[30] = {0x0};

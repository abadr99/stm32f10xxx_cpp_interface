/**
 * @file Iwdg-test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Iwdg.h"

uint32_t IwdgReg[4] = {0x0};
using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::iwdg;
using namespace stm32::registers::iwdg;

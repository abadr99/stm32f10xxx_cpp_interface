/**
 * @file EXTI-test.cpp
 * @author Manar
 * @brief 
 * @version 0.1
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"

using namespace stm32::utils::bit_manipulation;
using namespace stm32::registers::exti;

uint32_t AFIOReg[7] = {0x0};
uint32_t EXTIReg[6] = {0x0};

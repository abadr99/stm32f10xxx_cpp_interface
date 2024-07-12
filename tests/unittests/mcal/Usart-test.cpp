/**
 * @file Usart-test.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-06-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Usart.h"

uint32_t USART1Reg[7] ={};
uint32_t USART2Reg[7] ={};
uint32_t USART3Reg[7] ={};

using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::usart;
using namespace stm32::registers::usart;



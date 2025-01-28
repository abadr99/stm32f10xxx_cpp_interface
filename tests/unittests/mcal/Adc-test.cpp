/**
 * @file ADC-test.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Adc.h"

uint32_t ADC1Reg[20] = {0x0};
uint32_t ADC2Reg[20] = {0x0};
using namespace stm32::util;
using namespace stm32::dev::mcal::adc;
using namespace stm32::registers::adc;

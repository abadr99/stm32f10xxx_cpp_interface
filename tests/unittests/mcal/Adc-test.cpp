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
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Adc.h"

uint32_t ADCReg[20] = {0x0};
using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::adc;
using namespace stm32::registers::adc;

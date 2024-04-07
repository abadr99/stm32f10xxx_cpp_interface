/**
 * @file Pin-test.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"

uint32_t GPIOAReg[10];
uint32_t GPIOBReg[10];
uint32_t GPIOCReg[10];

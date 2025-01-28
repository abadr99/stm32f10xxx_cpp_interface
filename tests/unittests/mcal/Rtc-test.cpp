/**
 * @file Rtc-test.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Rtc.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::rtc;
using namespace stm32::registers::rtc;

uint32_t RtcReg[10] = {0x0};

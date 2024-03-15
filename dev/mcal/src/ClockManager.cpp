/**
 * @file ClockManager.cpp
 * @brief 
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Assert.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/ClockManager.h"

using namespace stm32::dev::mcal::rcc;           // NOLINT
using namespace stm32::dev::mcal::clock_manager; // NOLINT
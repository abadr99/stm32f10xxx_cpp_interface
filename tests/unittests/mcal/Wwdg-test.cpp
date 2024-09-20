/** 
 * @file Iwdg-test.cpp 
 * @author noran
 * @brief  
 * @version 0.1 
 * @date 2024-07-27 
 *  
 * @copyright Copyright (c) 2024 
 *  
 */ 
#include <gtest/gtest.h> 
#include "BitManipulation.h" 
#include "stm32f103xx.h" 
#include "Wwdg.h" 
 
uint32_t WwdgReg[3] = {0x0}; 
using namespace stm32::util; 
using namespace stm32::dev::mcal::wwdg; 
using namespace stm32::registers::wwdg;

/**
 * @file RCC.cpp
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-03-8
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "utils/inc/BitManipulation.h"
#include "utils/inc/Math.h"

#include "mcal/inc/Rcc.h"
#include "mcal/inc/stm32f103xx.h"

using namespace stm32::dev::mcal::rcc;
using namespace stm32::registers::rcc;

static void InitSysClock(ClkConfig config, ClkMultFactor multFactor)
{
    /*pll off*/
    RCC->CR.PLLON = 0;
    if (multFactor == Clkx1)
    {
        /*do nothing*/
    }
    else
    {
        RCC->CFGR.PLLMUL = multFactor;
    }
    /*config clk sys*/
    switch (config){
        case kHsi:
            RCC->CR.HSION = 1;
            /*wait until hsi is ready*/
            while (RCC->CR.HSIRDY == 0);
            /*set if pll*/
            RCC->CFGR.PLLSRC = 0;
        break;
        case kHse :
            RCC->CR.HSEON = 1;
            RCC->CFGR.PLLXTPRE = 0;
            /*wait until hse is ready*/
            while (RCC->CR.HSERDY == 0);
            /*set if pll*/
            RCC->CFGR.PLLSRC = 1;
        break;
        case kHseDivBy2 :
            RCC->CR.HSEON = 1;
            RCC->CFGR.PLLXTPRE = 1;
            /*wait until hse is ready*/
            while (RCC->CR.HSERDY == 0);
            /*set if pll*/
            RCC->CFGR.PLLSRC = 1;
        break;
    }
    /*pll on*/
    RCC->CR.PLLON = 1;
    /*wait until hse is ready*/
    while (RCC->CR.PLLON == 0);
    /*enable clk sys*/


}

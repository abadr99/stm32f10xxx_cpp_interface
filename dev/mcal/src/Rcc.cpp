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

void InitSysClock(ClkConfig config, PLL_MulFactor mulFactor)
{

    if ( config == kHsi  && mulFactor == kClock_1x)
    {
        /* Enable HSI */
        RCC->CR.HSION = 1;
        /*wait until hsi is ready*/
        while (RCC->CR.HSIRDY == 0);

        /* Switch to HSI */
        RCC->CFGR.SW=0;

    }else if ( config == kHse && mulFactor == kClock_1x)
    {
        /* Enable HSE */
        RCC->CR.HSEON = 1;
        /*wait until hse is ready*/
        while (RCC->CR.HSERDY == 0);
        /* Switch to HSE */
        RCC->CFGR.SW=1;

    }else if ( mulFactor != kClock_1x )
    {
        /* Disable PLL before configuring the PLL */
        RCC->CR.PLLON = 0;
        /* Set Multiplication factor */
        RCC->CFGR.PLLMUL = mulFactor;
        /* Chose PLL entry */
        if ( config == kHsi )
        {
            /* Enable HSI */
            RCC->CR.HSION = 1;
            /*wait until hsi is ready*/
            while (RCC->CR.HSIRDY == 0);
            /* Chose HSI as PLL entry clock source */
            RCC->CFGR.PLLSRC = 0;

        }else if ( config == kHse || config == kHseDivBy2)
        {
            /* Enable HSE */
            RCC->CR.HSEON = 1;
            /*wait until hse is ready*/
            while (RCC->CR.HSERDY == 0);
            /* Chose HSE as PLL entry clock source */
            RCC->CFGR.PLLSRC = 1;

            /* Set HSE divider */
            if ( config == kHse)
            {
                /* HSE is not divided */
                RCC->CFGR.PLLXTPRE =1;
            }else
            {
                /* HSE is not divided */
                RCC->CFGR.PLLXTPRE =0;
            }
        }
        /*Enable PLL */
        RCC->CR.PLLON = 1;
        /*wait until hse is ready*/
        while (RCC->CR.PLLON == 0);

        /* Switch to PLL */
        RCC->CFGR.SW = 2;
    }
    
}

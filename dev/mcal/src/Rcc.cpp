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
#include "utils/inc/Assert.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/stm32f103xx.h"

using namespace stm32::dev::mcal::rcc; // NOLINT[build/namespaces] 
using namespace stm32::registers::rcc; // NOLINT[build/namespaces] 

// Some asserts to make sure RCC struct members are in correct orders
ASSERT_STRUCT_SIZE(RccRegDef, (sizeof(RegWidth_t) * 10));

ASSERT_MEMBER_OFFSET(RccRegDef, CR,         0);
ASSERT_MEMBER_OFFSET(RccRegDef, CFGR,       sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(RccRegDef, CIR,        sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(RccRegDef, APB2RSTR,   sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(RccRegDef, APB1RSTR,   sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(RccRegDef, AHBENR,     sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(RccRegDef, APB2ENR,    sizeof(RegWidth_t) * 6);
ASSERT_MEMBER_OFFSET(RccRegDef, APB1ENR,    sizeof(RegWidth_t) * 7);
ASSERT_MEMBER_OFFSET(RccRegDef, BDCR,       sizeof(RegWidth_t) * 8);
ASSERT_MEMBER_OFFSET(RccRegDef, CSR,        sizeof(RegWidth_t) * 9);

void Rcc::InitSysClock(ClkConfig config, PLL_MulFactor mulFactor) {

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


void Rcc::SetAHBPrescaler(AHP_ClockDivider divFactor)
{
    if ( divFactor >= kAhpNotDivided && divFactor <= kAhpDiv512)
    {
        RCC->CFGR.HPRE = divFactor;
    }else
    {
        /* do nothing */
    }
}

void Rcc::SetAPB1Prescaler(APB_ClockDivider divFactor)
{
    if ( divFactor >= kApbNotDivided && divFactor <= kApbDiv16)
    {
        RCC->CFGR.PPRE1 = divFactor;
    }else
    {
        /* do nothing */
    }
}
void Rcc::SetAPB2Prescaler(APB_ClockDivider divFactor)
{
    if ( divFactor >= kApbNotDivided && divFactor <= kApbDiv16)
    {
        RCC->CFGR.PPRE2 = divFactor;
    }else
    {
        /* do nothing */
    }
}
void Rcc::SetMCOPinClk(McoModes mode)
{
        /* Validate input argument */
    if ( mode == kMcoNoClock || mode == kMcoHsi || 
         mode == kMcoHse     || mode == kMcoPll) 
    {
        RCC->CFGR.MCO = mode;
    }else 
    {
        /* Do Nothing */
    }
}
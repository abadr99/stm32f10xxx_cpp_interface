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

#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Assert.h"
#include "mcal/inc/Rcc.h"

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

static void WaitToReady(ClkConfig config);

void Rcc::InitSysClock(ClkConfig config, PLL_MulFactor mulFactor) {
    if (config == kHsi  && mulFactor == kClock_1x) {
        RCC->CR.HSION = 1;
        WaitToReady(config);
        RCC->CFGR.SW = 0;
    } else if (config == kHse && mulFactor == kClock_1x) {
        RCC->CR.HSEON = 1;
        WaitToReady(config);
        RCC->CFGR.SW = 1;

        // Enable Clk Dector to detect when clock failure
        RCC->CR.CSSON = 1;
    } else if (config == kPll) {
        //  Disable PLL before configuring the PLL
        RCC->CR.PLLON = 0;
        if (mulFactor != kClock_1x) {
            RCC->CFGR.PLLMUL = mulFactor;
        }
        if (config == kHsi) {
            RCC->CR.HSION = 1;
            WaitToReady(config);
            RCC->CFGR.PLLSRC = 0;

        } else if (config == kHse || config == kHseDivBy2) {
            RCC->CR.HSEON = 1;
            WaitToReady(config);

            // Chose HSE as PLL entry clock source
            RCC->CFGR.PLLSRC = 1;

            // Set HSE divider
            if (config == kHse) {
                RCC->CFGR.PLLXTPRE = 0;
            } else {
                RCC->CFGR.PLLXTPRE = 1;
            }
        }
        RCC->CR.PLLON = 1;
        WaitToReady(config);

        // Switch to PLL
        RCC->CFGR.SW = 2;
    }
}

void Rcc::SetAHBPrescaler(AHP_ClockDivider divFactor) {
    if (divFactor >= kAhpNotDivided && divFactor <= kAhpDiv512) {
        RCC->CFGR.HPRE = divFactor;
    }
}

void Rcc::SetAPB1Prescaler(APB_ClockDivider divFactor) {
    if (divFactor >= kApbNotDivided && divFactor <= kApbDiv16) {
        RCC->CFGR.PPRE1 = divFactor;
    }
}
void Rcc::SetAPB2Prescaler(APB_ClockDivider divFactor) {
    if (divFactor >= kApbNotDivided && divFactor <= kApbDiv16) {
        RCC->CFGR.PPRE2 = divFactor;
    }
}
void Rcc::SetMCOPinClk(McoModes mode) {
    if (mode == kMcoNoClock || mode == kMcoHsi ||
        mode == kMcoHse     || mode == kMcoPll) {
        RCC->CFGR.MCO = mode;
    }
}
void WaitToReady(ClkConfig config) {
    uint16_t countTimeOut = 0;
    if (config == kHsi) {
        while (RCC->CR.HSIRDY == 0 && countTimeOut != RCC_TIMEOUT) {
            countTimeOut++;
        }
    } else if (config == kHse) {
        while (RCC->CR.HSERDY == 0 && countTimeOut != RCC_TIMEOUT) {
            countTimeOut++;
        }
    } else {
        while (RCC->CR.PLLRDY == 0 && countTimeOut != RCC_TIMEOUT) {
            countTimeOut++;
        }
    }
    STM32_ASSERT(countTimeOut != RCC_TIMEOUT);
}

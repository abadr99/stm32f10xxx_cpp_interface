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

// We have three modes to initiate system clock:
// 1) Using Internal High Speed Clock i.e. HSI
// 2) Using External High Speed Clock i.e. HSE
// 3) Using PLL with certain multiplication factor and source where PLL sources:
//    3.a) HSI   3.b) HSE   3.c) HSE/2
void Rcc::InitSysClock(const ClkConfig& config,
                       const PLL_MulFactor& mulFactor) {
    if (config == kHsi  && mulFactor == kClock_1x) {          // 1) -- HSI
        SetInternalHighSpeedClk();
        return;
    } else if (config == kHse && mulFactor == kClock_1x) {    // 2) -- HSE
        SetExternalHighSpeedClk();
        return;
    }

    // 3) -- PLL
    auto GetPllSrc = [&]() -> PllSource {
        switch (config) {
            case kHsi:       return PllSource::kPllSource_Hsi;
            case kHse:       return PllSource::kPllSource_Hse;
            case kHseDivBy2: return PllSource::kPllSource_HseDiv2;
            default:         return PllSource::kPllSource_Unkown;
        }
    };

    // --- DISABLE PLL BEFORE CONFIGURE
    RCC->CR.PLLON = 0;

    SetPllFactor(mulFactor);

    SetPllSource(GetPllSrc());

    // --- ENABLE PLL AFTER CONFIGURATION
    RCC->CR.PLLON = 1;
    WaitToReady(kPLLRDY);
    RCC->CFGR.SW = 2;    // Switch to PLL
}

void Rcc::SetAHBPrescaler(const AHP_ClockDivider& divFactor) {
    STM32_ASSERT(divFactor >= kAhpNotDivided && divFactor <= kAhpDiv512);
    RCC->CFGR.HPRE = divFactor;
}

void Rcc::SetAPB1Prescaler(const APB_ClockDivider& divFactor) {
    STM32_ASSERT(divFactor >= kApbNotDivided && divFactor <= kApbDiv16);
    RCC->CFGR.PPRE1 = divFactor;
}

void Rcc::SetAPB2Prescaler(const APB_ClockDivider& divFactor) {
    STM32_ASSERT(divFactor >= kApbNotDivided && divFactor <= kApbDiv16);
    RCC->CFGR.PPRE2 = divFactor;
}

void Rcc::SetMCOPinClk(const McoModes& mode) {
    STM32_ASSERT(mode == kMcoNoClock ||
                 mode == kMcoSystemClock ||
                 mode == kMcoHsi ||
                 mode == kMcoHse ||
                 mode == kMcoPll);
    RCC->CFGR.MCO = mode;
}

void Rcc::AdjustInternalClock(uint8_t CalibrationValue) {
    RCC->CR.HSITRIM = CalibrationValue;
}

void Rcc::WaitToReady(Flags flag) {
    uint16_t ctr = 0;

    switch (flag) {
        case kHSIRDY: while ((!(RCC->CR.HSIRDY)) && (ctr != RCC_TIMEOUT) && (++ctr));  break;    // NOLINT
        case kHSERDY: while ((!(RCC->CR.HSERDY)) && (ctr != RCC_TIMEOUT) && (++ctr));  break;    // NOLINT
        case kPLLRDY: while ((!(RCC->CR.PLLRDY)) && (ctr != RCC_TIMEOUT) && (++ctr));  break;    // NOLINT
    }

    STM32_ASSERT(ctr != RCC_TIMEOUT);
}

void Rcc::SetInternalHighSpeedClk() {
    RCC->CR.HSION = 1;
    WaitToReady(kHSIRDY);
    RCC->CFGR.SW = 0;
}

void Rcc::SetExternalHighSpeedClk() {
    RCC->CR.HSEON = 1;
    WaitToReady(kHSERDY);
    RCC->CFGR.SW = 1;
    RCC->CR.CSSON = 1;
}

void Rcc::SetPllFactor(PLL_MulFactor factor) {
    if (factor == PLL_MulFactor::kClock_1x) {
        return;
    }
    RCC->CFGR.PLLMUL = factor;
}

void Rcc::SetPllSource(PllSource src) {
    STM32_ASSERT(src == kPllSource_Hsi ||
                 src == kPllSource_Hse ||
                 src == kPllSource_HseDiv2);
    switch (src) {
        case kPllSource_Hsi:
            RCC->CR.HSION = 1;
            WaitToReady(kPLLRDY);
            RCC->CFGR.PLLSRC = 0;
            return;
        case kPllSource_Hse:
        case kPllSource_HseDiv2:
            RCC->CR.HSEON = 1;
            WaitToReady(kPLLRDY);
            RCC->CFGR.PLLSRC = 1;
            RCC->CFGR.PLLXTPRE = src == kPllSource_Hse ? 0 : 1;
            return;
    }
}
void Rcc::SetExternalClock(const HSE_Type HseType ) {
    STM32_ASSERT(HseType == kHseCrystal || HseType == kHseRC);
    RCC->CR.HSEON = 0;
    RCC->CR.HSEBYP = HseType == kHseCrystal ? 0 : 1;
}

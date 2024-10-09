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

#include "mcal/stm32f103xx.h"
#include "utils/Util.h"
#include "utils/Constant.h"
#include "utils/Assert.h"
#include "mcal/Rcc.h"

using namespace stm32;
using namespace stm32::dev::mcal::rcc; 
using namespace stm32::registers::rcc; 

// Error Massages Used by the Logger
#define RCC_MCO_PIN_MODE_ERROR          "Invalid MCO PIN Mode"
#define RCC_PLL_SOURCE_ERROR            "Invalid PLL Source"
#define RCC_EXTERNAL_CLOCK_SOURCE_ERROR "Invalid External Clock Source"
#define RCC_AHB_PRESCALER_ERROR         "Invalid AHB Prescaler"
#define RCC_APB1_PRESCALER_ERROR        "Invalid APB1 Prescaler"
#define RCC_APB2_PRESCALER_ERROR        "Invalid APB2 Prescaler"
#define RCC_TIME_OUT_ERROR              "Timeout while waiting for a flag to be ready."
#define RCC_EMPTY_MESSAGE               ""

// Some asserts to make sure RCC struct members are in correct orders
ASSERT_STRUCT_SIZE(RccRegDef, (sizeof(RegWidth_t) * 12));

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
    if (config == kHsi  && mulFactor == kClock_1x) {    // 1) -- HSI
        SetInternalHighSpeedClk();
        return;
    } 
    if (config == kHse && mulFactor == kClock_1x) {    // 2) -- HSE
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
    STM32_ASSERT((divFactor >= kAhpNotDivided) && (divFactor <= kAhpDiv512), RCC_AHB_PRESCALER_ERROR);  // NOLINT
    RCC->CFGR.HPRE = divFactor;
}

void Rcc::SetAPB1Prescaler(const APB_ClockDivider& divFactor) {
    STM32_ASSERT((divFactor >= kApbNotDivided) && (divFactor <= kApbDiv16), RCC_APB1_PRESCALER_ERROR);  // NOLINT
    RCC->CFGR.PPRE1 = divFactor;
}

void Rcc::SetAPB2Prescaler(const APB_ClockDivider& divFactor) {
    STM32_ASSERT((divFactor >= kApbNotDivided) && (divFactor <= kApbDiv16), RCC_APB2_PRESCALER_ERROR);  // NOLINT
    RCC->CFGR.PPRE2 = divFactor;
}

void Rcc::SetMCOPinClk(const McoModes& mode) {
    STM32_ASSERT(mode == kMcoNoClock ||
                 mode == kMcoSystemClock ||
                 mode == kMcoHsi ||
                 mode == kMcoHse ||
                 mode == kMcoPll,
                 RCC_MCO_PIN_MODE_ERROR);
    RCC->CFGR.MCO = mode;
}

void Rcc::AdjustInternalClock(uint8_t CalibrationValue) {
    RCC->CR.HSITRIM = CalibrationValue;
}

void Rcc::WaitToReady(Flags flag) {
    switch (flag) {
        case kHSIRDY: util::BusyWait<constant::TimeOut::kRcc>([&](){ return !RCC->CR.HSIRDY; });  break;    // NOLINT [whitespace/line_length]
        case kHSERDY: util::BusyWait<constant::TimeOut::kRcc>([&](){ return !RCC->CR.HSERDY; });  break;    // NOLINT [whitespace/line_length]
        case kPLLRDY: util::BusyWait<constant::TimeOut::kRcc>([&](){ return !RCC->CR.PLLRDY; });  break;    // NOLINT [whitespace/line_length]
        default: STM32_ASSERT(1, RCC_EMPTY_MESSAGE);
    }
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
                 src == kPllSource_HseDiv2,
                 RCC_PLL_SOURCE_ERROR);
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
    STM32_ASSERT((HseType == kHseCrystal) || (HseType == kHseRC), RCC_EXTERNAL_CLOCK_SOURCE_ERROR);
    RCC->CR.HSEON = 0;
    RCC->CR.HSEBYP = HseType == kHseCrystal ? 0 : 1;
}

void Rcc::Enable(Peripheral p) {
    switch (p) {
        #define P(name_, bridge_)\
            case Peripheral::k##name_: RCC->bridge_##ENR.name_##EN = 1; break;
        PERIPHERALS
        #undef P
        default: STM32_ASSERT(0, RCC_EMPTY_MESSAGE); break;
    }
}

void Rcc::Disable(Peripheral p) {
    switch (p) {
        #define P(name_, bridge_)\
            case Peripheral::k##name_: RCC->bridge_##RSTR.name_##RST = 1; break;
        PERIPHERALS
        #undef P
        default: STM32_ASSERT(0, RCC_EMPTY_MESSAGE); break;
    }
}

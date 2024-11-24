/**
 * @file Power.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Assert.h"
#include "utils/Types.h"
#include "mcal/Power.h"

using namespace stm32::registers::nvic;
using namespace stm32::registers::pwr;
using namespace stm32::dev::mcal::pwr;

#define TO_STRING(str_)  #str_

#define PWR_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Pwr error_)

#define __WFI() __asm volatile ("wfi")
#define __WFE() __asm volatile ("wfe")

#define Pwr_EMPTY_MESSAGE               ""
volatile PwrRegDef* Pwr::PWR = nullptr;

void Pwr::Init() {
        PWR = reinterpret_cast<volatile PwrRegDef*>(Addr<Peripheral::kPWR >::getBaseAddr());
} 
void Pwr::EnterSleepMode(PwrEntry sleepEntry, SleepType type) {
    STM32_ASSERT((sleepEntry == PwrEntry::kWFI) ||
                 (sleepEntry == PwrEntry::kWFE), PWR_CONFIG_ERROR(PwrEntry));
    STM32_ASSERT((type == SleepType::kSleepNow) ||
                 (type == SleepType::kSleepOnExit), PWR_CONFIG_ERROR(SleepType));
    //  Set sleep on exit behavior
    SCB->SCR.SLEEPONEXIT = static_cast<uint8_t>(type);
    //  Ensure standard sleep mode
    SCB->SCR.SLEEPDEEP = 0;
    EnterLowPowerMode(sleepEntry);
}
void Pwr::EnterStopMode(PwrEntry stopEntry, PwrRegulator regulator) {
    STM32_ASSERT((stopEntry == PwrEntry::kWFI) ||
                 (stopEntry == PwrEntry::kWFE), PWR_CONFIG_ERROR(PwrEntry));
    STM32_ASSERT((regulator == PwrRegulator::kOn) ||
                 (regulator == PwrRegulator::kLowPower), PWR_CONFIG_ERROR(PwrRegulator));
    //  Select the voltage regulator mode
    PWR->CR.LPDS = regulator == PwrRegulator::kLowPower ? 1 : 0;
    //  Ensure entering stop mode, not standby
    PWR->CR.PDDS = 0;
    //  Enable deep sleep mode
    SCB->SCR.SLEEPDEEP = 1;
    EnterLowPowerMode(stopEntry);
}
void Pwr::EnterStandbyMode(PwrEntry standbyEntry) {
    STM32_ASSERT((standbyEntry == PwrEntry::kWFI) ||
                 (standbyEntry == PwrEntry::kWFE), PWR_CONFIG_ERROR(PwrEntry));
    // Select standby mode
    PWR->CR.PDDS = 1;
    // Enable deep sleep mode
    SCB->SCR.SLEEPDEEP = 1;
    PWR->CSR.WUF = 0;
    EnterLowPowerMode(standbyEntry);
}
void Pwr::WakeupPinState(State state) {
    PWR->CSR.EWUP = state == State::kDisable ? 0 : 1;
}

void Pwr::ClearFlag(PwrFlag flag) {
    switch (flag) {
        case PwrFlag::kWU : PWR->CR.CWUF = 1; break;
        case PwrFlag::kSB : PWR->CR.CSBF = 1; break;
        default: STM32_ASSERT(0, Pwr_EMPTY_MESSAGE); 
    }
}
#ifndef UNIT_TEST
void Pwr::EnterLowPowerMode(PwrEntry entry) {
    STM32_ASSERT((entry == PwrEntry::kWFI) ||
                 (entry == PwrEntry::kWFE), PWR_CONFIG_ERROR(PwrEntry));
    if (entry == PwrEntry::kWFI) {
        __WFI();  // Wait for interrupt
    } else if (entry == PwrEntry::kWFE) {
        __WFE();  // Wait for event
    }
}
#else 
void Pwr::EnterLowPowerMode(PwrEntry entry) {
    /* DO NO THING */
    // This fake lambda is used to avoid warning for un_used
    // variable 'enty' as we want this function to have the same
    // signature as one in non UNIT_TEST mode
    auto FakeLambda = [entry](){ return entry; };
    FakeLambda();
}
#endif

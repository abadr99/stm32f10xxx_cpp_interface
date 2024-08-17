/**
 * @file Power.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "Power.h"

using namespace stm32::registers::nvic;
using namespace stm32::registers::pwr;
using namespace stm32::dev::mcal::pwr;

#define __WFI() __asm volatile ("wfi")
#define __WFE() __asm volatile ("wfe")

void Pwr::EnterSleepMode(PwrEntry sleepEntry, SleepType type) {
    //  Set sleep on exit behavior
    SCB->SCR.SLEEPONEXIT = static_cast<uint8_t>(type);
    //  Ensure standard sleep mode
    SCB->SCR.SLEEPDEEP = 0;
    
    #ifndef UNIT_TEST
        EnterLowPowerMode(sleepEntry);
    #endif
}
void Pwr::EnterStopMode(PwrEntry stopEntry, PwrRegulator regulator) {
    //  Select the voltage regulator mode
    if (regulator == PwrRegulator::kLowPower) {
        PWR->CR.LPDS = 1;
    } else if (regulator == PwrRegulator::kOn) {
        PWR->CR.LPDS = 0;
    }
    //  Ensure entering stop mode, not standby
    PWR->CR.PDDS = 0;
    //  Enable deep sleep mode
    SCB->SCR.SLEEPDEEP = 1;
    
    #ifndef UNIT_TEST
        EnterLowPowerMode(stopEntry);
    #endif
}
void Pwr::EnterStandbyMode(PwrEntry standbyEntry) {
    // Select standby mode
    PWR->CR.PDDS = 1;
    // Enable deep sleep mode
    SCB->SCR.SLEEPDEEP = 1;
    PWR->CSR.WUF = 0;
    
    #ifndef UNIT_TEST
        EnterLowPowerMode(standbyEntry);
    #endif
}
void Pwr::WakeupPinState(State state) {
    if (state == State::kDisable) {
        PWR->CSR.EWUP = 0;
    } else if (state == State::kEnable) {
        PWR->CSR.EWUP = 1;
    }
}
void Pwr::ClearFlag(PwrFlag flag) {
    if (flag == PwrFlag::kWU) {
        PWR->CR.CWUF = 1;
    } else if (flag == PwrFlag::kSB) {
        PWR->CR.CSBF = 1;
    }
}
#ifndef UNIT_TEST
void Pwr::EnterLowPowerMode(PwrEntry entry) {
    if (entry == PwrEntry::kWFI) {
        __WFI();  // Wait for interrupt
    } else if (entry == PwrEntry::kWFE) {
        __WFE();  // Wait for event
    }
}
#endif

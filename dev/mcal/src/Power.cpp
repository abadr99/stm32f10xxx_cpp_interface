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

void Pwr::EnterSleepMode(PwrEntry sleepEntry) {
    SCB->SCR.SLEEPDEEP = 0;
    if (sleepEntry == kWFI) {
        __WFI();
    } else if (sleepEntry == kWFE) {
        __WFE();
    }
}
void Pwr::EnterStopMode(PwrRegulater regulater, PwrEntry stopEntry) {
    PWR->CR.PDDS = 0;
    if (regulater == kLowPower) {
        PWR->CR.LPDS = 1;
    } else if (regulater == kOn) {
        PWR->CR.LPDS = 0;
    }
    SCB->SCR.SLEEPDEEP = 1;
    if (stopEntry == kWFI) {
        __WFI();
    } else if (stopEntry == kWFE) {
        __WFE();
    }
}
void Pwr::EnterStandbyMode(PwrEntry standbyEntry) {
    PWR->CR.PDDS = 1;
    SCB->SCR.SLEEPDEEP = 1;
    if (standbyEntry == kWFI) {
        __WFI();
    } else if (standbyEntry == kWFE) {
        __WFE();
    }
}
void Pwr::WakeupPinState(State state) {
    if (state == kDisable) {
        PWR->CSR.EWUP = 0;
    } else if (state == kEnable) {
        PWR->CSR.EWUP = 1;
    }
}
void Pwr::ClearFlag(PwrFlag flag) {
    if (flag == kWU) {
        PWR->CR.CWUF = 1;
    } else if (flag == kSB) {
        PWR->CR.CSBF = 1;
    }
}

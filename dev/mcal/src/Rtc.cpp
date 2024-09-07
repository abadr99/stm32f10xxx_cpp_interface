/**
 * @file Rtc.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "mcal/inc/stm32f103xx.h"
#include "Assert.h"
#include "Types.h"
#include "Util.h"
#include "Rtc.h"

using namespace stm32::dev::mcal::rtc;
using namespace stm32::registers::rtc;
using namespace stm32::type;          

pFunction Rtc::pRtcCallBackFunctions[3] = {nullptr, nullptr, nullptr};

void Rtc::Init(const RtcConfig &config) {
    // wait for the last operation to be done
    WaitForLastTask();

    // Enter Configuration mode
    EnterConfigMode();

    // Set the RTC prescaler value
    SetPrescaler(config.prescaler_value);

    // Set the RTC counter value
    SetCounterValue(config.counter_value);

    // Set the RTC alarm value
    SetAlarmValue(config.alarm_value);

    // Set interrupt service routines
    SetSecondISR(config.SecondISR);
    SetAlarmISR(config.AlarmISR);
    SetOverflowISR(config.OverflowISR);

    // Exit RTC configuration mode
    ExitConfigMode();

    // wait for the last operation to be done
    WaitForLastTask();

    // wait for the Synchronization between the RTC Registers
    WaitForSync();
}

void Rtc::AlarmInterruptEnable(void) {
    RTC->CRH.ALRIE = 1;
}
void Rtc::SecondInterruptEnable(void) {
    RTC->CRH.SECIE = 1;
}
void Rtc::OverflowInterruptEnable(void) {
    RTC->CRH.OWIE = 1;
}

void Rtc::AlarmInterruptDisable(void) {
    RTC->CRH.ALRIE = 0;
}
void Rtc::SecondInterruptDisable(void) {
    RTC->CRH.SECIE = 0;
}
void Rtc::OverflowInterruptDisable(void) {
    RTC->CRH.OWIE = 0;
}
void Rtc::Enable(void) {
    // TODO(@MRefat): either enable it here or from the RCC in the application code
}

void Rtc::Disable(void) {
    // TODO(@MRefat): either enable it here or from the RCC in the application code
}

void Rtc::EnterConfigMode(void) {
    RTC->CRL.CNF = 1;
}
void Rtc::ExitConfigMode(void) {
    RTC->CRL.CNF = 0;
}
void Rtc::SetPrescaler(uint32_t prescaler_value) {
    WaitForLastTask();
    RTC->PRLH.PRL = (prescaler_value >> 16) & 0x000F;
    RTC->PRLL.PRL = prescaler_value & 0xFFFF;
    WaitForLastTask();
}

void Rtc::SetAlarmValue(uint32_t alarm_value) {
    WaitForLastTask();
    RTC->ALRH.ALR = (alarm_value >> 16) & 0xFFFF;
    RTC->ALRL.ALR = alarm_value & 0xFFFF;
    WaitForLastTask();
}

void Rtc::SetCounterValue(uint32_t time_in_seconds) {
    WaitForLastTask();
    RTC->CNTH.CNT = (time_in_seconds >> 16) & 0xFFFF;
    RTC->CNTL.CNT = time_in_seconds & 0xFFFF;
    WaitForLastTask();
}

void Rtc::GetCurrentTime(Time *pCurrent_time) {
    uint32_t counter_value = (RTC->CNTH.CNT << 16) | RTC->CNTL.CNT;
    uint32_t seconds_into_day =  counter_value % 86400;
    pCurrent_time->second = seconds_into_day % 60;
    pCurrent_time->minutes = (seconds_into_day % 3600) / 60;
    pCurrent_time->hour = seconds_into_day / 3600;
}

void Rtc::WaitForLastTask(void) {
    util::BusyWait<constant::TimeOut::kRtc>([&](){ return RTC->CRL.RTOFF == 0; });
}

void Rtc::WaitForSync(void) {
    // Clear Registers synchronized flag
    RTC->CRL.RSF = 0;
    // Wait for RSF to be set
    util::BusyWait<constant::TimeOut::kRtc>([&](){ return RTC->CRL.RSF == 0; });
}

void Rtc::SetAlarmISR(pFunction fun) {
    pRtcCallBackFunctions[0] = fun;
}

void Rtc::SetOverflowISR(pFunction fun) {
    pRtcCallBackFunctions[1] = fun;
}

void Rtc::SetSecondISR(pFunction fun) {
    pRtcCallBackFunctions[2] = fun;
}

pFunction Rtc::GetAlarmISR(void) {
    return pRtcCallBackFunctions[0];
}

pFunction Rtc::GetOverflowISR(void) {
    return pRtcCallBackFunctions[1];
}

pFunction Rtc::GetSecondISR(void) {
    return pRtcCallBackFunctions[2];
}

extern "C" void RTCAlarm_IRQHandler(void) {
    // TODO(MRefat): wake up the processor form the standby mode
    pFunction fun = Rtc::GetAlarmISR();
    if (fun != nullptr) {
        fun();
    }
}

extern "C" void RTC_IRQHandler(void) {
    pFunction fun = nullptr;
    if ((RTC->CRL.ALRF == 1) && (RTC->CRH.ALRIE == 1)) {
        fun = Rtc::GetAlarmISR();
        if (fun != nullptr) {
            fun();
        }
        RTC->CRL.ALRF = 0;
    }

    if ((RTC->CRL.SECF == 1) && (RTC->CRH.SECIE == 1)) {
        fun = Rtc::GetSecondISR();
        if (fun != nullptr) {
            fun();
        }
        RTC->CRL.SECF = 0;
    }

    if ((RTC->CRL.OWF == 1) && (RTC->CRH.OWIE == 1)) {
        fun = Rtc::GetAlarmISR();
        if (fun != nullptr) {
            fun();
        }
        RTC->CRL.OWF = 0;
    }
}

/**
 * @file Timer.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-5
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "mcal/Timer.h"

using namespace stm32::dev::mcal::timer;
using namespace stm32::registers::timer;
using namespace stm32::util;
using namespace stm32::type;

#define TIMER_EMPTY_MESSAGE               ""

#define TO_STRING(str_)  #str_

#define TIMER_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Timer error_)

pFunction Timer::pGlobalCallBackFunction[5] = {nullptr};

template<Peripheral peripheralT>
using adr = stm32::constant::Address<peripheralT>;

Timer::Timer(const TimerConfig & config): config_(config) {
    switch (config_.Timerid) {
        case kTimer1 : 
            timerReg = reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM1>::Get()); 
            break;
        case kTimer2 : 
            timerReg = reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM2>::Get()); 
            break;
        case kTimer3 : 
            timerReg = reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM3>::Get()); 
            break;
        case kTimer4 : 
            timerReg = reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM4>::Get()); 
            break;
        case kTimer5 : 
            timerReg = reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM5>::Get()); 
            break; 
        default: 
            STM32_ASSERT(0, TIMER_EMPTY_MESSAGE); 
            break;
    }   
    Init();
}
    
void Timer::Init() {
    STM32_ASSERT(((config_.Timerid >= kTimer1) &&
                 (config_.Timerid <= kTimer5)), TIMER_CONFIG_ERROR(TimerID));
    // Set Interrupt update
    timerReg->DIER.UIE = config_.interrupt;
    pGlobalCallBackFunction[config_.Timerid] = config_.pfunction;
}
typename Timer::timerRegDefPtr Timer::GetPtr(TimerID id) {
    switch (id) {
        case kTimer1 : return reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM1>::Get());
        case kTimer2 : return reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM2>::Get());
        case kTimer3 : return reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM3>::Get()); 
        case kTimer4 : return reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM4>::Get());
        case kTimer5 : return reinterpret_cast<timerRegDefPtr>(adr<Peripheral::kTIM5>::Get()); 
        default: 
            STM32_ASSERT(0, TIMER_EMPTY_MESSAGE); 
            break;
        }   
}

void Timer::Delay_ms(const TimeBaseTypeDef & counter, uint16_t value) {
    // Set prescaler value
    timerReg->PSC = config_.Prescaler-1;
    // Set counter Direction
    timerReg->CR1.DIR = config_.Direction;
    timerReg->CR1.ARPE = kEnable;
    // Disable Timer at first
    timerReg->CR1.CEN = 0;
    // Set preLoad value
    timerReg->ARR = value-1;
    // Set Clock Division
    timerReg->CR1.CKD = counter.ClkDivision;
}
// Channel 1 , Timer 2
void Timer::OCMode(const TimerOCTypeDef & OC ) {
    // Disable Timer at first
    timerReg->CR1.CEN = 0;

    timerReg->PSC = config_.Prescaler-1;
        // Set counter Direction
    timerReg->CR1.DIR = config_.Direction;
    timerReg->CR1.ARPE = kEnable;

    /* Set the Output Compare Polarity */
    timerReg->CCER.CC1P = OC.polarity;

    /* Initialize all the registers */
    timerReg->EGR.UG = 1;


    timerReg->BDTR.MOE = 1;
}
void Timer::SetCompare1(const TimerOCTypeDef & OC, TimerChannels channel, uint16_t pwmvalue) {
    timerReg->CR1.CEN = 0;
    // Set preLoad value
    timerReg->ARR = OC.period - 1;
    // timerReg->CCR1 = pwmvalue;
        switch (channel) {
        case kChannel1:  //  PORTA_0
            timerReg->CCMR1.CC1S = 0;
            timerReg->CCMR1.OC1M = OC.mode;
            timerReg->CCMR1.OC1PE = kEnable;
            /* Set the Output State */
            timerReg->CCER.CC1E = OC.state;
            timerReg->CCR1 = 0;
            timerReg->CCR1 = pwmvalue;
            break;
            case kChannel2:  //  PORTA_1:
            timerReg->CCMR1.CC2S = 0;   // Channel as output
            timerReg->CCMR1.OC2M = OC.mode;   // PWM mode 1
            timerReg->CCMR1.OC2PE = kEnable;  // Enable preload
            timerReg->CCER.CC2E = OC.state;    // Enable output
            timerReg->CCR2 = pwmvalue;
            break;
        case kChannel3:  //  PORTA_2:
            timerReg->CCMR2.CC3S = 0;   // Channel as output
            timerReg->CCMR2.OC3M = OC.mode;   // PWM mode 1
            timerReg->CCMR2.OC3PE = kEnable;  // Enable preload
            timerReg->CCER.CC3E = OC.state;    // Enable output
            timerReg->CCR3 = pwmvalue;
            break;
        case kChannel4:  //  PORTA_3:
            timerReg->CCR4 = pwmvalue;
            break;
        }
        timerReg->EGR.UG = 1;
        Timer::Cmd(kEnable);
}
void Timer::Cmd(State state) {
    timerReg->CR1.CEN = state;
}

pFunction Timer::GetFunToISR(TimerID id) {
    STM32_ASSERT((id >= kTimer1) &&
                 (id <= kTimer5), TIMER_CONFIG_ERROR(TimerID));
    return pGlobalCallBackFunction[id];
}
extern "C" void TIM1_UP_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer1);
    Timer::GetPtr(kTimer1)->SR.UIF ^= 1;
    func();
}

extern "C" void TIM1_CC_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer1);
    Timer::GetPtr(kTimer1)->SR.CC1IF ^= 1;
    func();
}

extern "C" void TIM2_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer2);
    Timer::GetPtr(kTimer2)->SR.UIF ^= 1;
    func();
}

extern "C" void TIM3_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer3);
    Timer::GetPtr(kTimer3)->SR.UIF ^= 1;
    func();
}

extern "C" void TIM4_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer4);
    Timer::GetPtr(kTimer4)->SR.UIF ^= 1;
    func();
}

extern "C" void TIM5_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer5);
    Timer::GetPtr(kTimer5)->SR.UIF ^= 1;
    func();
}
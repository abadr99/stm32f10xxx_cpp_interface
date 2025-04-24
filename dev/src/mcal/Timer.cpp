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
        // Clear CC1S (bits 1:0), OC1M (6:4), OC1PE (3)
        timerReg->CCMR1 &= ~((3 << 0) | (7 << 4) | (1 << 3));
        // Set OC1M mode and enable preload
        timerReg->CCMR1 |= ((OC.mode & 0x7) << 4) | (1 << 3);

        /*timerReg->CCMR1.CC1S = 0;
        timerReg->CCMR1.OC1M = OC.mode;
        timerReg->CCMR1.OC1PE = kEnable;*/
        /* Set the Output State */
        timerReg->CCER.CC1E = OC.state;
        timerReg->CCR1 = 0;
        timerReg->CCR1 = pwmvalue;
        break;
    case kChannel2:  // PORTA_1:
        // Clear CC2S (bits 9:8), OC2M (14:12), OC2PE (11)
        timerReg->CCMR1 &= ~((3 << 8) | (7 << 12) | (1 << 11));
        // Set OC2M mode and enable preload
        timerReg->CCMR1 |= ((OC.mode & 0x7) << 12) | (1 << 11);
        /*timerReg->CCMR1.CC2S = 0;   // Channel as output
        timerReg->CCMR1.OC2M = OC.mode;   // PWM mode 1
        timerReg->CCMR1.OC2PE = kEnable;  // Enable preload*/
        timerReg->CCER.CC2E = OC.state;    // Enable output
        timerReg->CCR2 = pwmvalue;
        break;
    case kChannel3:  // PORTA_2:
        // Clear CC3S (1:0), OC3M (6:4), OC3PE (3) in CCMR2
        timerReg->CCMR2 &= ~((3 << 0) | (7 << 4) | (1 << 3));
        // Set OC3M and preload
        timerReg->CCMR2 |= ((OC.mode & 0x7) << 4) | (1 << 3);
        /*timerReg->CCMR2.CC3S = 0;   // Channel as output
        timerReg->CCMR2.OC3M = OC.mode;   // PWM mode 1
        timerReg->CCMR2.OC3PE = kEnable;  // Enable preload*/
        timerReg->CCER.CC3E = OC.state;    // Enable output
        timerReg->CCR3 = pwmvalue;
        break;
    case kChannel4:  // PORTA_3:
        timerReg->CCR4 = pwmvalue;
        break;
    }
    timerReg->EGR.UG = 1;
    Timer::Cmd(kEnable);
}
void Timer::ICMode(TimerChannels channel, TimerICTypeDef IC) {
    // Disable timer during configuration
    Timer::Cmd(kDisable);

    switch (channel) {
        case kChannel1:
            // Clear CC1S [1:0], IC1PSC [3:2], IC1F [7:4]
            timerReg->CCMR1 &= ~((3 << 0) | (3 << 2) | (0xF << 4));
            // Set selection, prescaler, and filter
            timerReg->CCMR1 |= ((IC.selection & 0x3) << 0) |
                               ((IC.prescaler & 0x3) << 2) |
                               ((IC.filter & 0xF) << 4);
            /*timerReg->CCMR1.CC1S = IC.selection;    // Select input source
            timerReg->CCMR1.IC1PSC = IC.prescaler;  // Set prescaler
            timerReg->CCMR1.IC1F = IC.filter;       // Set input filter*/
            timerReg->CCER.CC1P = IC.polarity;      // Set polarity
            timerReg->CCER.CC1E = 1;                // Enable capture
            break;
        case kChannel2:
            // Clear CC2S [9:8], IC2PSC [11:10], IC2F [15:12]
            timerReg->CCMR1 &= ~((3 << 8) | (3 << 10) | (0xF << 12));
            timerReg->CCMR1 |= ((IC.selection & 0x3) << 8) |
                               ((IC.prescaler & 0x3) << 10) |
                               ((IC.filter & 0xF) << 12);
            /*timerReg->CCMR1.CC2S = IC.selection;
            timerReg->CCMR1.IC2PSC = IC.prescaler;
            timerReg->CCMR1.IC2F = IC.filter;*/
            timerReg->CCER.CC2P = IC.polarity;
            timerReg->CCER.CC2E = 1;
            break;
        case kChannel3:
            // Clear CC3S [1:0], IC3PSC [3:2], IC3F [7:4] in CCMR2
            timerReg->CCMR2 &= ~((3 << 0) | (3 << 2) | (0xF << 4));
            timerReg->CCMR2 |= ((IC.selection & 0x3) << 0) |
                               ((IC.prescaler & 0x3) << 2) |
                               ((IC.filter & 0xF) << 4);
            /*timerReg->CCMR2.CC3S = IC.selection;
            timerReg->CCMR2.IC3PSC = IC.prescaler;
            timerReg->CCMR2.IC3F = IC.filter;*/
            timerReg->CCER.CC3P = IC.polarity;
            timerReg->CCER.CC3E = 1;
            break;
        case kChannel4:
            // Clear CC4S [9:8], IC4PSC [11:10], IC4F [15:12] in CCMR2
            timerReg->CCMR2 &= ~((3 << 8) | (3 << 10) | (0xF << 12));
            timerReg->CCMR2 |= ((IC.selection & 0x3) << 8) |
                               ((IC.prescaler & 0x3) << 10) |
                               ((IC.filter & 0xF) << 12);
            /*timerReg->CCMR2.CC4S = IC.selection;
            timerReg->CCMR2.IC4PSC = IC.prescaler;
            timerReg->CCMR2.IC4F = IC.filter;*/
            timerReg->CCER.CC4P = IC.polarity;
            timerReg->CCER.CC4E = 1;
            break;
    }

    // Enable timer
    Timer::Cmd(kEnable);
}

uint16_t Timer::GetCaptureValue(TimerChannels channel) {
    switch (channel) {
        case kChannel1: return timerReg->CCR1;
        case kChannel2: return timerReg->CCR2;
        case kChannel3: return timerReg->CCR3;
        case kChannel4: return timerReg->CCR4;
        default: return 0;
    }
}

void Timer::ClearCaptureFlag(TimerChannels channel) {
    switch (channel) {
        case kChannel1: timerReg->SR.CC1IF = 0; break;
        case kChannel2: timerReg->SR.CC2IF = 0; break;
        case kChannel3: timerReg->SR.CC3IF = 0; break;
        case kChannel4: timerReg->SR.CC4IF = 0; break;
    }
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

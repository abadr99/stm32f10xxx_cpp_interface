/**
 * @file Can.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-12-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "mcal/Rcc.h"
#include "mcal/Can.h"

using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::can;
using namespace stm32::registers::can;

void Can::Init(const CanConfig &conf) {
    SetOperatingMode(conf, kInitialization);

    CAN->MCR.TTCM = conf.TTCM;
    CAN->MCR.ABOM = conf.ABOM;
    CAN->MCR.AWUM = conf.AWUM;
    CAN->MCR.NART = conf.NART;
    CAN->MCR.RFLM = conf.RFLM;
    CAN->MCR.TXFP = conf.priority;

    CAN->BTR = (uint32_t)((uint32_t)conf.mode << 30) | \
               ((uint32_t)conf.SJW << 24) | \
               ((uint32_t)conf.BS1 << 16) | \
               ((uint32_t)conf.BS2 << 20) | \
               ((uint32_t)conf.prescaler - 1);

    SetOperatingMode(conf, kNormal);
}
void Can::SetOperatingMode(const CanConfig &conf, OperatingMode mode) {
    if (mode == kSleep) {
        if (conf.opMode == kInitialization) {
            CAN->MCR.INRQ = 0;
            CAN->MCR.SLEEP = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.SLAK; });
        } else if (conf.opMode == kNormal) {
            CAN->MCR.SLEEP = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.SLAK; });
        }
    } else if (mode == kInitialization) {
        if (conf.opMode == kSleep) {
            CAN->MCR.INRQ = 1;
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.INAK; });
        } else if (conf.opMode == kNormal) {
            CAN->MCR.INRQ = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.INAK; });
        }
    } else if (mode == kNormal) {
        if (conf.opMode == kSleep) {
            CAN->MCR.INRQ = 0;
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return !(CAN->MSR.INAK || 
                                                                        CAN->MSR.SLAK); });
        } else if (conf.opMode == kInitialization) {
            CAN->MCR.INRQ = 0;
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return !(CAN->MSR.INAK && 
                                                                        CAN->MSR.SLAK); });
        }
    }
}

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

void Can::SetOperatingMode(const CanConfig &conf, OperatingMode mode) {
    if (mode == kSleep) {
        if (conf.mode == kInitialization) {
            CAN->MCR.INRQ = 0;
            CAN->MCR.SLEEP = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.SLAK; });
        } else if (conf.mode == kNormal) {
            CAN->MCR.SLEEP = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.SLAK; });
        }
    } else if (mode == kInitialization) {
        if (conf.mode == kSleep) {
            CAN->MCR.INRQ = 1;
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.INAK; });
        } else if (conf.mode == kNormal) {
            CAN->MCR.INRQ = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.INAK; });
        }
    } else if (mode == kNormal) {
        if (conf.mode == kSleep) {
            CAN->MCR.INRQ = 0;
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return !(CAN->MSR.INAK || 
                                                                        CAN->MSR.SLAK); });
        } else if (conf.mode == kInitialization) {
            CAN->MCR.INRQ = 0;
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return !(CAN->MSR.INAK && 
                                                                        CAN->MSR.SLAK); });
        }
    }
}

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

volatile CANRegDef* Can::CAN = nullptr;

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
void Can::FilterInit(const FilterConfig& conf) {
    CAN->FMR.FINIT = 1;
    CAN->FA1R.registerVal &= ~(conf.bank);
    if (conf.scale == k16it) {
        CAN->FS1R.registerVal &= ~(conf.bank);
        CAN->FilterRegister[conf.bank].FR1 = ((conf.maskIdLow & 0x0000FFFF)  << 16 | 
                                              (conf.idLow & 0x0000FFFF));
        CAN->FilterRegister[conf.bank].FR2 = ((conf.maskIdHigh & 0x0000FFFF) << 16 | 
                                              (conf.idHigh & 0x0000FFFF));
    } else {
        CAN->FS1R.registerVal |= (conf.bank);
        CAN->FilterRegister[conf.bank].FR1 = ((conf.idHigh & 0x0000FFFF)     << 16 | 
                                              (conf.idLow & 0x0000FFFF));
        CAN->FilterRegister[conf.bank].FR2 = ((conf.maskIdHigh & 0x0000FFFF) << 16 | 
                                              (conf.maskIdLow & 0x0000FFFF));
    }
    switch (conf.mode) {
        case kMask: CAN->FM1R.registerVal &= ~(conf.bank); break;
        case kList: CAN->FM1R.registerVal |=  (conf.bank); break;
    }
    switch (conf.fifoAssign) {
        case kFIFO0: CAN->FFA1R.registerVal &= ~(conf.bank); break;
        case kFIFO1: CAN->FFA1R.registerVal |=  (conf.bank); break;
    }
    if (conf.activation == kEnable) {
        CAN->FA1R.registerVal |= (conf.bank); 
    }
    CAN->FMR.FINIT = 0;
}
void Can::Transmit(CanTxMsg message) {
    uint32_t txMailbox = 0;
    if ((CAN->TSR.TME0 != 0) || 
        (CAN->TSR.TME1 != 0) ||
        (CAN->TSR.TME2 != 0)) {
            txMailbox = CAN->TSR.CODE;
            if (txMailbox <= 2) {
                if (message.ide == kStd) {
                    CAN->TxMailBox[txMailbox].TIR.STID = message.stdId;
                    CAN->TxMailBox[txMailbox].TIR.RTR = message.rtr;
                } else {
                    CAN->TxMailBox[txMailbox].TIR.STID = message.extId;
                    CAN->TxMailBox[txMailbox].TIR.RTR = message.rtr;
                    CAN->TxMailBox[txMailbox].TIR.IDE = 1;
                }
                CAN->TxMailBox[txMailbox].TDTR.DLC = message.dlc;
                for (uint8_t i = 0; i < message.dlc; ++i) {
                    if (i < 4) {
                        CAN->TxMailBox[txMailbox].TDLR |= (message.data[i] << (i * 8));
                    } else {
                        CAN->TxMailBox[txMailbox].TDHR |= (message.data[i] << ((i - 4) * 8));
                    }
                }
                CAN->TxMailBox[txMailbox].TIR.TXRQ = 1;
            }
        }
}
void Can::CancelTransmit(MailBoxType mailbox) {
    switch (mailbox) {
        case kMailBox0 : CAN->TSR.ABRQ0; break;
        case kMailBox1 : CAN->TSR.ABRQ1; break;
        case kMailBox2 : CAN->TSR.ABRQ2; break;
    }
}
void Can::Receive(CanRxMsg message, FifoNumber fifo) {
    message.ide = (IdType)CAN->RxFIFOMailBox[fifo].RIR.IDE;
    if (message.ide == kStd) {
        message.stdId = CAN->RxFIFOMailBox[fifo].RIR.STID;
    } else {
        message.extId = CAN->RxFIFOMailBox[fifo].RIR.EXID;
    }
    message.rtr = (RTRType)CAN->RxFIFOMailBox[fifo].RIR.RTR;
    message.dlc = (uint8_t)CAN->RxFIFOMailBox[fifo].RDTR.DLC;
    message.FMI = CAN->RxFIFOMailBox[fifo].RDTR.FMI;
    for (uint8_t i =0; i < message.dlc; ++i) {
        if (i < 4) {
            message.data[i] = (CAN->RxFIFOMailBox[fifo].RDLR >> (i * 8));
        } else {
            message.data[i] = (CAN->RxFIFOMailBox[fifo].RDHR >> ((i - 4) * 8));
        }
    }
    if (fifo == kFIFO0) {
        CAN->RF0R.RFOM0 = 1;
    } else {
        CAN->RF1R.RFOM1 = 1;
    }
}
uint8_t Can::GetPendingMessages(FifoNumber fifo) {
    uint8_t message = 0;
    if (fifo == kFIFO0) {
        message = CAN->RF0R.FMP0;
    } else {
        message = CAN->RF1R.FMP1;
    }
    return message;
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

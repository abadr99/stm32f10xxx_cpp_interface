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
#define TO_STRING(str_)  #str_

#define CAN_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Can error_)
// --- HELPER MACRO TO CHECK IF WE ARE USING CORRECT CAN CONFIGURATIONS
#define CHECK_CAN_CONFIG()\
    STM32_ASSERT((conf.buadRate >= k100KBPS)\
              && (conf.buadRate <= k1MBPS), CAN_CONFIG_ERROR(Prescaler));\
    STM32_ASSERT((conf.opMode >= kSleep)\
              && (conf.opMode <= kNormal), CAN_CONFIG_ERROR(OperatingMode));\
    STM32_ASSERT((conf.mode >= kSilent)\
              && (conf.mode <= kCombined), CAN_CONFIG_ERROR(TestMode));\
    STM32_ASSERT((conf.priority >= kID)\
              && (conf.priority <= kRequest), CAN_CONFIG_ERROR(FifoPriority));\
    STM32_ASSERT((conf.sjw >= k1tq)\
              && (conf.sjw <= k4tq), CAN_CONFIG_ERROR(TimeQuanta));\
    STM32_ASSERT((conf.bs1 >= k1tq)\
              && (conf.bs1 <= k16tq), CAN_CONFIG_ERROR(TimeQuanta));\
    STM32_ASSERT((conf.bs2 >= k1tq)\
              && (conf.bs2 <= k8tq), CAN_CONFIG_ERROR(TimeQuanta));\
    STM32_ASSERT((conf.TTCM >= kDisable)\
              && (conf.TTCM <= kEnable), CAN_CONFIG_ERROR(State));\
    STM32_ASSERT((conf.ABOM >= kDisable)\
              && (conf.ABOM <= kEnable), CAN_CONFIG_ERROR(State));\
    STM32_ASSERT((conf.AWUM >= kDisable)\
              && (conf.AWUM <= kEnable), CAN_CONFIG_ERROR(State));\
    STM32_ASSERT((conf.NART >= kDisable)\
              && (conf.NART <= kEnable), CAN_CONFIG_ERROR(State));\
    STM32_ASSERT((conf.RFLM >= kDisable)\
              && (conf.RFLM <= kEnable), CAN_CONFIG_ERROR(State));

#define CHECK_FILTER_CONFIG()\
    STM32_ASSERT((conf.mode >= kMask)\
          && (conf.mode <= kList), CAN_CONFIG_ERROR(FilterMode));\
    STM32_ASSERT((conf.fifoAssign >= kFIFO0)\
          && (conf.fifoAssign <= kFIFO1), CAN_CONFIG_ERROR(FifoNumber));\
    STM32_ASSERT((conf.scale >= k16bit)\
          && (conf.scale <= k32bit), CAN_CONFIG_ERROR(FilterScale));\
    STM32_ASSERT((conf.activation >= kDisable)\
          && (conf.activation <= kEnable), CAN_CONFIG_ERROR(State));

#define CHECK_MESSAGE_CONFIG()\
    STM32_ASSERT((message.ide >= kStd)\
              && (message.ide <= kExt), CAN_CONFIG_ERROR(IdType));\
    STM32_ASSERT((message.rtr >= kData)\
              && (message.rtr <= kRemote), CAN_CONFIG_ERROR(RTRType));

  
void Can::Init(const CanConfig &conf) {
    CHECK_CAN_CONFIG();
    //  Exit from sleep mode
    SetOperatingMode(conf, kInitialization);

    CAN->MCR.TTCM = conf.TTCM;      //  Set the time triggered communication mode
    CAN->MCR.ABOM = conf.ABOM;      //  Set the automatic bus-off management
    CAN->MCR.AWUM = conf.AWUM;      //  Set the automatic wake-up mode
    CAN->MCR.NART = conf.NART;      //  Set the no automatic retransmission
    CAN->MCR.RFLM = conf.RFLM;      //  Set the receive FIFO locked mode
    CAN->MCR.TXFP = conf.priority;  //  Set the transmit FIFO priority

    //  Set the bit timing register
    CAN->BTR = (uint32_t)((uint32_t)conf.mode << 30) | \
               ((uint32_t)conf.sjw << 24) | \
               ((uint32_t)conf.bs1 << 16) | \
               ((uint32_t)conf.bs2 << 20) | \
               ((uint32_t)conf.buadRate - 1);

    //  Request leave initialisation
    SetOperatingMode(conf, kNormal);
}
void Can::FilterInit(const FilterConfig& conf) {
    CHECK_FILTER_CONFIG();

    CAN->FMR.FINIT = 1;  //  Initialisation mode for the filter
    CAN->FA1R.registerVal &= ~(conf.bank);  //  Filter Deactivation

    if (conf.scale == k16bit) {
        CAN->FS1R.registerVal &= ~(conf.bank);
        /* First 16-bit identifier and First 16-bit mask
	       Or First 16-bit identifier and Second 16-bit identifier */
        CAN->FilterRegister[conf.bank].FR1 = ((conf.maskIdLow & 0x0000FFFF)  << 16 | 
                                              (conf.idLow & 0x0000FFFF));
        /* Second 16-bit identifier and Second 16-bit mask
	       Or Third 16-bit identifier and Fourth 16-bit identifier */                                
        CAN->FilterRegister[conf.bank].FR2 = ((conf.maskIdHigh & 0x0000FFFF) << 16 | 
                                              (conf.idHigh & 0x0000FFFF));
    } else {
        CAN->FS1R.registerVal |= (conf.bank);
        //  32-bit identifier or First 32-bit identifier
        CAN->FilterRegister[conf.bank].FR1 = ((conf.idHigh & 0x0000FFFF)     << 16 | 
                                              (conf.idLow & 0x0000FFFF));
        //  32-bit mask or Second 32-bit identifier
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
    //  Leave the initialisation mode for the filter
    CAN->FMR.FINIT = 0;
}
void Can::Transmit(CanTxMsg message) {
    CHECK_MESSAGE_CONFIG();
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
    STM32_ASSERT((mailbox >= kMailBox0) && (mailbox <= kMailBox2), CAN_CONFIG_ERROR(MailBoxType));
    switch (mailbox) {
        case kMailBox0 : CAN->TSR.ABRQ0; break;
        case kMailBox1 : CAN->TSR.ABRQ1; break;
        case kMailBox2 : CAN->TSR.ABRQ2; break;
    }
}
void Can::Receive(CanRxMsg message, FifoNumber fifo) {
    CHECK_MESSAGE_CONFIG();
    STM32_ASSERT((fifo >= kFIFO0) && (fifo <= kFIFO1), CAN_CONFIG_ERROR(FifoNumber));
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
    STM32_ASSERT((fifo >= kFIFO0) && (fifo <= kFIFO1), CAN_CONFIG_ERROR(FifoNumber));
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

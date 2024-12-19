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
#include "utils/BitManipulation.h"
#include "mcal/Rcc.h"
#include "mcal/Can.h"

using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::can;
using namespace stm32::registers::can;

volatile CANRegDef* Can::CAN = nullptr;
  
void Can::Init(const CanConfig &conf) {
    //  Exit from sleep mode
    SetOperatingMode(conf, OperatingMode::kInitialization);

    CAN->MCR.TTCM = static_cast<uint32_t>(conf.TTCM);
    CAN->MCR.AWUM = static_cast<uint32_t>(conf.AWUM);
    CAN->MCR.ABOM = static_cast<uint32_t>(conf.ABOM);
    CAN->MCR.RFLM = static_cast<uint32_t>(conf.RFLM);
    CAN->MCR.NART = static_cast<uint32_t>(conf.NART);
    CAN->MCR.TXFP = static_cast<uint32_t>(conf.priority);

    //  Set the bit timing register
    CAN->BTR = WriteBits<uint32_t, 30, 31>(CAN->BTR, static_cast<uint32_t>(conf.mode));
    CAN->BTR = WriteBits<uint32_t, 24, 25>(CAN->BTR, static_cast<uint32_t>(conf.sjw));
    CAN->BTR = WriteBits<uint32_t, 20, 22>(CAN->BTR, static_cast<uint32_t>(conf.bs2));
    CAN->BTR = WriteBits<uint32_t, 16, 19>(CAN->BTR, static_cast<uint32_t>(conf.bs1));
    CAN->BTR = WriteBits<uint32_t, 0, 9>  
                        (CAN->BTR, static_cast<uint32_t>(static_cast<uint32_t>(conf.buadRate) - 1));

    //  Request leave initialisation
    SetOperatingMode(conf, OperatingMode::kNormal);
}
void Can::FilterInit(const FilterConfig& conf) {
    CAN->FMR.FINIT = 1;  //  Initialisation mode for the filter
    CAN->FA1R.registerVal = ClearBit(CAN->FA1R.registerVal, conf.bank);  //  Filter Deactivation

    if (conf.scale == k16bit) {
        CAN->FS1R.registerVal = ClearBit(CAN->FS1R.registerVal, conf.bank);
        CAN->FilterRegister[conf.bank].FR1 = 
            WriteBits<uint32_t, 16, 31>(CAN->FilterRegister[conf.bank].FR1, conf.maskIdLow &0xFFFF);
        CAN->FilterRegister[conf.bank].FR1 = 
            WriteBits<uint32_t, 0, 15>(CAN->FilterRegister[conf.bank].FR1, conf.idLow &0xFFFF);
        CAN->FilterRegister[conf.bank].FR2 = 
            WriteBits<uint32_t, 16, 31>(CAN->FilterRegister[conf.bank].FR2, conf.maskIdHigh &0xFFFF);   //  NOLINT
        CAN->FilterRegister[conf.bank].FR2 = 
            WriteBits<uint32_t, 0, 15>(CAN->FilterRegister[conf.bank].FR2, conf.idHigh &0xFFFF);

    } else {
        CAN->FS1R.registerVal = SetBit(CAN->FA1R.registerVal, conf.bank);
        CAN->FilterRegister[conf.bank].FR1 = 
            WriteBits<uint32_t, 16, 31>(CAN->FilterRegister[conf.bank].FR1, conf.idHigh &0xFFFF);
        CAN->FilterRegister[conf.bank].FR1 = 
            WriteBits<uint32_t, 0, 15>(CAN->FilterRegister[conf.bank].FR1, conf.idLow &0xFFFF);
        CAN->FilterRegister[conf.bank].FR2 = 
            WriteBits<uint32_t, 16, 31>(CAN->FilterRegister[conf.bank].FR2, conf.maskIdHigh &0xFFFF);   //  NOLINT
        CAN->FilterRegister[conf.bank].FR2 = 
            WriteBits<uint32_t, 0, 15>(CAN->FilterRegister[conf.bank].FR2, conf.maskIdLow &0xFFFF);
    }
    CAN->FM1R.registerVal = (conf.mode == FilterMode::kMask) ?
    ClearBit(CAN->FM1R.registerVal, conf.bank) : SetBit(CAN->FM1R.registerVal, conf.bank);
    CAN->FFA1R.registerVal = (conf.fifoAssign == FifoNumber::kFIFO0) ?
    ClearBit(CAN->FFA1R.registerVal, conf.bank) : SetBit(CAN->FFA1R.registerVal, conf.bank);
    if (conf.activation == State::kEnable) {
        CAN->FA1R.registerVal = SetBit(CAN->FA1R.registerVal, conf.bank); 
    }
    //  Leave the initialisation mode for the filter
    CAN->FMR.FINIT = 0;
}
void Can::Transmit(CanTxMsg message) {
    uint32_t txMailbox = 0;
    auto isMailBoxAvailable =[&]() ->bool {
        return (CAN->TSR.TME0 != 0) || (CAN->TSR.TME1 != 0) || (CAN->TSR.TME2 != 0);
    };
    if (isMailBoxAvailable()) {
            txMailbox = CAN->TSR.CODE;
            if (txMailbox <= 2) {
                CAN->TxMailBox[txMailbox].TIR.STID = message.stdId;
                CAN->TxMailBox[txMailbox].TIR.RTR = static_cast<uint32_t>(message.rtr);
                CAN->TxMailBox[txMailbox].TIR.IDE = (message.ide == IdType::kExt) ? 1 : 0;
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
        case MailBoxType::kMailBox0 : CAN->TSR.ABRQ0 = 1; break;
        case MailBoxType::kMailBox1 : CAN->TSR.ABRQ1 = 1; break;
        case MailBoxType::kMailBox2 : CAN->TSR.ABRQ2 = 1; break;
    }
}
void Can::Receive(CanRxMsg message, FifoNumber fifo) {
    uint32_t fifoIndex = static_cast<uint32_t>(fifo);
    message.ide = static_cast<IdType>(CAN->RxFIFOMailBox[fifoIndex].RIR.IDE);

    if (message.ide == IdType::kStd) {
        message.stdId = CAN->RxFIFOMailBox[fifoIndex].RIR.STID;
    } else {
        message.extId = CAN->RxFIFOMailBox[fifoIndex].RIR.EXID;
    }
    message.rtr = (RemoteTxReqType)CAN->RxFIFOMailBox[fifoIndex].RIR.RTR;
    message.dlc = (uint8_t)CAN->RxFIFOMailBox[fifoIndex].RDTR.DLC;
    message.FMI = CAN->RxFIFOMailBox[fifoIndex].RDTR.FMI;
    for (uint8_t i =0; i < message.dlc; ++i) {
        if (i < 4) {
            message.data[i] = (CAN->RxFIFOMailBox[fifoIndex].RDLR >> (i * 8));
        } else {
            message.data[i] = (CAN->RxFIFOMailBox[fifoIndex].RDHR >> ((i - 4) * 8));
        }
    }
    if (fifo == FifoNumber::kFIFO0) {
        CAN->RF0R.RFOM0 = 1;
    } else {
        CAN->RF1R.RFOM1 = 1;
    }
}
uint8_t Can::GetPendingMessages(FifoNumber fifo) {
    return (fifo == FifoNumber::kFIFO0) ? CAN->RF0R.FMP0 : CAN->RF1R.FMP1;
}
void Can::SetOperatingMode(const CanConfig &conf, OperatingMode mode) {
    if (mode == OperatingMode::kSleep) {
        if (conf.opMode == OperatingMode::kInitialization) { CAN->MCR.INRQ = 0; }
            CAN->MCR.SLEEP = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.SLAK; });
    } else if (mode == OperatingMode::kInitialization) {
        if (conf.opMode == OperatingMode::kSleep) { CAN->MCR.SLEEP = 0; }
            CAN->MCR.INRQ = 1;
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return CAN->MSR.INAK; });
    } else if (mode == OperatingMode::kNormal) {
        if (conf.opMode == OperatingMode::kSleep) {
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return !(CAN->MSR.INAK || 
                                                                        CAN->MSR.SLAK); });
        } else if (conf.opMode == OperatingMode::kInitialization) {
            util::BusyWait<constant::TimeOut::kDefault>([&](){ return !(CAN->MSR.INAK && 
                                                                        CAN->MSR.SLAK); });
        }
        CAN->MCR.INRQ = 0;
        CAN->MCR.SLEEP = 0;
    }
}

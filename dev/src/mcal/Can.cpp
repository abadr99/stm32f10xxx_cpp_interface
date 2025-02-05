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
    CAN = reinterpret_cast<volatile CANRegDef*>(Addr<Peripheral::kCAN>::Get());

    //  Exit from sleep mode
    /*
    CAN->MCR.INRQ = 1;
    util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.INAK); });
    CAN->MCR.SLEEP = 0; 
    util::BusyWait<constant::TimeOut::kCan>([&](){ return !(CAN->MSR.SLAK); });
    */

    SetOperatingMode(conf, OperatingMode::kInitialization);

    CAN->MCR.TTCM = static_cast<uint32_t>(conf.TTCM);
    CAN->MCR.ABOM = static_cast<uint32_t>(conf.ABOM);
    CAN->MCR.AWUM = static_cast<uint32_t>(conf.AWUM);
    CAN->MCR.NART = static_cast<uint32_t>(conf.NART);
    CAN->MCR.RFLM = static_cast<uint32_t>(conf.receivedFifoLock);
    CAN->MCR.TXFP = static_cast<uint32_t>(conf.priority);

    //  Set the bit timing register
    CAN->BTR = WriteBits<uint32_t, 30, 31>(CAN->BTR, static_cast<uint32_t>(conf.testMode));
    CAN->BTR = WriteBits<uint32_t, 24, 25>(CAN->BTR, static_cast<uint32_t>(conf.sjw));
    CAN->BTR = WriteBits<uint32_t, 20, 22>(CAN->BTR, static_cast<uint32_t>(conf.bs2));
    CAN->BTR = WriteBits<uint32_t, 16, 19>(CAN->BTR, static_cast<uint32_t>(conf.bs1));
    CAN->BTR = WriteBits<uint32_t, 0, 9>  
            (CAN->BTR, static_cast<uint32_t>(static_cast<uint32_t>(conf.baudRatePrescaler) - 1));

    //  Request abort transmission
    CAN->TSR.ABRQ0 = 1;
    CAN->TSR.ABRQ1 = 1;
    CAN->TSR.ABRQ2 = 1;

    //  Request release receive FIFO
    CAN->RF0R.RFOM0 = 1;
    CAN->RF1R.RFOM1 = 1;
    //  Request leave initialisation
    SetOperatingMode(conf, OperatingMode::kNormal);
    /*
    auto IsTimeOut = [&](){ return !(CAN->MSR.INAK || CAN->MSR.SLAK); };
    if (conf.opMode == OperatingMode::kSleep) {
        CAN->MCR.SLEEP = 0;
        util::BusyWait<constant::TimeOut::kCan>(IsTimeOut);
    } else if (conf.opMode == OperatingMode::kInitialization) {
        CAN->MCR.INRQ = 0;
        util::BusyWait<constant::TimeOut::kCan>(IsTimeOut);
    }
    */
}
void Can::FilterInit(const FilterConfig& conf) {
    CAN->FMR.FINIT = 1;  //  Initialisation mode for the filter
    CAN->FA1R.registerVal = ClearBit(CAN->FA1R.registerVal, conf.bank);  //  Filter Deactivation

    auto ComputeFilterVal = [](uint16_t lo, uint16_t hi) -> RegWidth_t {
        RegWidth_t val = ExtractBits<uint16_t, 0, 15>(lo);
        return WriteBits<uint32_t, 16, 31>(val, ExtractBits<uint16_t, 0, 15>(hi));
    };
    
    // ---- SET FILTER VALUE
    if (conf.scale == FilterScale::k16bit) {
        CAN->FS1R.registerVal = ClearBit(CAN->FS1R.registerVal, conf.bank); 
        CAN->FilterRegister[conf.bank].FR1 = ComputeFilterVal(conf.idLow,  conf.maskIdLow);
        CAN->FilterRegister[conf.bank].FR2 = ComputeFilterVal(conf.idHigh, conf.maskIdHigh);
    } else {  // k32bit
        CAN->FS1R.registerVal = SetBit(CAN->FS1R.registerVal, conf.bank);
        // Compute and set FR1 and FR2
        CAN->FilterRegister[conf.bank].FR1 = ComputeFilterVal(conf.idLow, conf.idHigh);
        CAN->FilterRegister[conf.bank].FR2 = ComputeFilterVal(conf.maskIdLow, conf.maskIdHigh);
    }
    // --- SET FILTER MODE
    CAN->FM1R.registerVal = (conf.mode == FilterMode::kMask) 
                                ? ClearBit(CAN->FM1R.registerVal, conf.bank)
                                : SetBit(CAN->FM1R.registerVal, conf.bank);
    CAN->FFA1R.registerVal = (conf.fifoAssign == FifoNumber::kFIFO0) 
                                ? ClearBit(CAN->FFA1R.registerVal, conf.bank) 
                                : SetBit(CAN->FFA1R.registerVal, conf.bank);
    if (conf.activation == State::kEnable) {
        CAN->FA1R.registerVal = SetBit(CAN->FA1R.registerVal, conf.bank); 
    }
    //  Leave the initialisation mode for the filter
    CAN->FMR.FINIT = 0;
}

void Can::Transmit(const CanTxMsg& message) {
    uint32_t txMailbox = 0;
    auto IsMailBoxAvailable =[&]() -> bool {
        return (CAN->TSR.TME0 != 0) || 
               (CAN->TSR.TME1 != 0) || 
               (CAN->TSR.TME2 != 0);
    };
    
    // Helper function to get the next available mailbox
    auto GetAvailableMailbox = [&]() -> uint32_t {
        if (CAN->TSR.TME0) return 0;
        if (CAN->TSR.TME1) return 1;
        if (CAN->TSR.TME2) return 2;
        return 3;  // No mailbox available
    };
    
    if (IsMailBoxAvailable()) {
        txMailbox = GetAvailableMailbox();
        if (txMailbox <= 2) {
            CAN->TxMailBox[txMailbox].TIR.STID = message.stdId;
            CAN->TxMailBox[txMailbox].TIR.RTR = static_cast<uint32_t>(message.rtr);
            CAN->TxMailBox[txMailbox].TIR.IDE = (message.ide == IdType::kExId) ? 1 : 0;
            CAN->TxMailBox[txMailbox].TDTR.DLC = message.dlc;
            uint32_t hi = 0;
            uint32_t lo = 0;
            for (uint8_t i = 0; i < message.dlc; ++i) {
                if (i < 4) {
                    lo = WriteByte(lo, i, message.data[i]);
                } else {
                    hi = WriteByte(hi, i - 4, message.data[i]);
                }
            }
            CAN->TxMailBox[txMailbox].TDLR = lo;
            CAN->TxMailBox[txMailbox].TDHR = hi;
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

void Can::Receive(CanRxMsg& message, FifoNumber fifo) {  //  NOLINT [runtime/references]
    uint32_t fifoIndex = static_cast<uint32_t>(fifo);
    message.ide = static_cast<IdType>(CAN->RxFIFOMailBox[fifoIndex].RIR.IDE);
    if (message.ide == IdType::kStId) {
        message.stdId = CAN->RxFIFOMailBox[fifoIndex].RIR.STID;
    } else {
        message.extId = CAN->RxFIFOMailBox[fifoIndex].RIR.EXID;
    }
    message.rtr = (RemoteTxReqType)CAN->RxFIFOMailBox[fifoIndex].RIR.RTR;
    message.dlc = (uint8_t)CAN->RxFIFOMailBox[fifoIndex].RDTR.DLC;
    message.FMI = CAN->RxFIFOMailBox[fifoIndex].RDTR.FMI;
    for (uint8_t i = 0; i < message.dlc; ++i) {
        if (i < 4) {
            message.data[i] = ExtractByte(CAN->RxFIFOMailBox[fifoIndex].RDLR, i);
        } else {
            message.data[i] = ExtractByte(CAN->RxFIFOMailBox[fifoIndex].RDHR, i - 4);
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
    using OM = OperatingMode;
    
    auto OperateSleepMode = [&]() {
        CAN->MCR.SLEEP = 1;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return CAN->MSR.SLAK; });
    }; 
    
    auto OperateInitMode = [&]() {
        CAN->MCR.INRQ = 1;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.INAK == 0); });
        CAN->MCR.SLEEP = 0; 
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.SLAK ==1); });
    };
    
    auto OperateNormalMode = [&]() {
        auto IsTimeOut = [&](){ return !(CAN->MSR.INAK || CAN->MSR.SLAK); };
        if (conf.opMode == OperatingMode::kSleep) {
            CAN->MCR.SLEEP = 0;
            util::BusyWait<constant::TimeOut::kCan>(IsTimeOut);
        } else if (conf.opMode == OperatingMode::kInitialization) {
            CAN->MCR.INRQ = 0;
            util::BusyWait<constant::TimeOut::kCan>(IsTimeOut);
        }
    };

    switch (mode) {
        case OM::kSleep:          OperateSleepMode();   return;
        case OM::kInitialization: OperateInitMode();    return;
        case OM::kNormal:         OperateNormalMode();  return;
        default: /* TODO(@abadr99): Support Unreachable code */ break;
    }
}

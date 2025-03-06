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
pFunction Can::TxMailboxComplete[3] = {nullptr};
pFunction Can::TxMailboxAbort[3] = {nullptr};
pFunction Can::RxFifoMsgPending[2] = {nullptr};
pFunction Can::RxFifoFull[2] = {nullptr};
pFunction Can::SleepCallback = nullptr;
pFunction Can::WakeUpCallback = nullptr;
pFunction Can::ErrorCallback = nullptr;

void Can::Init(const CanConfig &conf) {
    CAN = reinterpret_cast<volatile CANRegDef*>(Addr<Peripheral::kCAN>::Get());

    //  Exit from sleep mode
    SetOperatingMode(OperatingMode::kInitialization);

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
}

void Can::Start() {
    SetOperatingMode(OperatingMode::kNormal);
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
    uint32_t txMailbox = 3;
     auto GetAvailableMailbox = [&]() -> uint8_t {
         uint8_t retMailBox = 3;
         if (CAN->TSR.TME0) retMailBox = 0;
         else if (CAN->TSR.TME1) retMailBox = 1;
         else if (CAN->TSR.TME2) retMailBox = 2;
         return retMailBox;  // No mailbox available
     };

     txMailbox = GetAvailableMailbox();

    if (txMailbox != 3) {
        CAN->TxMailBox[txMailbox].TIR.STID = message.stdId;
        CAN->TxMailBox[txMailbox].TIR.IDE = (message.ide == IdType::kExId) ? 1 : 0;
        CAN->TxMailBox[txMailbox].TIR.RTR = static_cast<uint32_t>(message.rtr);
        CAN->TxMailBox[txMailbox].TDTR.DLC = message.dlc;
        CAN->TxMailBox[txMailbox].TDLR = (((uint32_t)message.data[3] << 24)) |
                                         (((uint32_t)message.data[2] << 16)) |
                                         (((uint32_t)message.data[1] << 8))  |
                                         (((uint32_t)message.data[0]));
        CAN->TxMailBox[txMailbox].TDHR = (((uint32_t)message.data[7] << 24)) |
                                         (((uint32_t)message.data[6] << 16)) |
                                         (((uint32_t)message.data[5] << 8))  |
                                         (((uint32_t)message.data[4]));
        // Request Transmission
        CAN->TxMailBox[txMailbox].TIR.TXRQ = 1;
        
        
        if (txMailbox == 0) {
            //  Wait until the transmission ocures
            util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->TSR.TXOK0 == 1); });
        } else if (txMailbox == 1) {
            //  Wait until the transmission ocures
            util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->TSR.TXOK1 == 1); });
        } else if (txMailbox ==2) {
            util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->TSR.TXOK2 == 1); });
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
    
    // Check that the Rx FIFO [0,1] is empty
    if (fifo == FifoNumber::kFIFO0) {
        if (CAN->RF0R.FMP0 == 0) {
            return;
        }
    } else {
        if (CAN->RF1R.FMP1 == 0) {
            return;
        }
    } 
    message.ide = static_cast<IdType>(CAN->RxFIFOMailBox[fifoIndex].RIR.IDE);
    if (message.ide == IdType::kStId) {
        message.stdId = CAN->RxFIFOMailBox[fifoIndex].RIR.STID;
    } else {
        message.extId = CAN->RxFIFOMailBox[fifoIndex].RIR.EXID;
    }
    message.rtr = (RemoteTxReqType)CAN->RxFIFOMailBox[fifoIndex].RIR.RTR;
    if (CAN->RxFIFOMailBox[fifoIndex].RDTR.DLC >= 8) {
        message.dlc = 8;
    } else {
        message.dlc = CAN->RxFIFOMailBox[fifoIndex].RDTR.DLC;
    }
    message.FMI = CAN->RxFIFOMailBox[fifoIndex].RDTR.FMI;
    message.timeStamp = CAN->RxFIFOMailBox[fifoIndex].RDTR.TIME;

    message.data[0] = (uint8_t)0xFF & CAN->RxFIFOMailBox[fifoIndex].RDLR;
    message.data[1] = (uint8_t)(0xFF & (CAN->RxFIFOMailBox[fifoIndex].RDLR >> 8));
    message.data[2] = (uint8_t)(0xFF & (CAN->RxFIFOMailBox[fifoIndex].RDLR >> 16));
    message.data[3] = (uint8_t)(0xFF & (CAN->RxFIFOMailBox[fifoIndex].RDLR >> 24));
    message.data[4] = (uint8_t)(0xFF & CAN->RxFIFOMailBox[fifoIndex].RDHR);
    message.data[5] = (uint8_t)(0xFF & (CAN->RxFIFOMailBox[fifoIndex].RDHR >> 8));
    message.data[6] = (uint8_t)(0xFF & (CAN->RxFIFOMailBox[fifoIndex].RDHR >> 16));
    message.data[7] = (uint8_t)(0xFF & (CAN->RxFIFOMailBox[fifoIndex].RDHR >> 24));
    
    // Release the Mailbox of the FIFO
    if (fifo == FifoNumber::kFIFO0) {
        CAN->RF0R.RFOM0 = 1;
    } else {
        CAN->RF1R.RFOM1 = 1;
    }
}

uint8_t Can::GetPendingMessages(FifoNumber fifo) {
    return (fifo == FifoNumber::kFIFO0) ? CAN->RF0R.FMP0 : CAN->RF1R.FMP1;
}

void Can::EnableInterrupt(Interrupts interrupt) {
    CAN->IER = SetBit(CAN->IER, static_cast<uint32_t>(interrupt));
}

void Can::DisableInterrupt(Interrupts interrupt) {
    CAN->IER = ClearBit(CAN->IER, static_cast<uint32_t>(interrupt));
}

void Can::SetCallback(CallbackId id, pFunction func) {
    switch (id) {
        case CallbackId::kTxMailbox0Complete: TxMailboxComplete[0] = func; break;
        case CallbackId::kTxMailbox1Complete: TxMailboxComplete[1] = func; break;
        case CallbackId::kTxMailbox2Complete: TxMailboxComplete[2] = func; break;
        case CallbackId::kTxMailbox0Abort: TxMailboxAbort[0] = func; break;
        case CallbackId::kTxMailbox1Abort: TxMailboxAbort[1] = func; break;
        case CallbackId::kTxMailbox2Abort: TxMailboxAbort[2] = func; break;
        case CallbackId::kFifo0MessagePending: RxFifoMsgPending[0] = func; break;
        case CallbackId::kFifo1MessagePending: RxFifoMsgPending[1] = func; break;
        case CallbackId::kFifo0Full: RxFifoFull[0] = func; break;
        case CallbackId::kFifo1Full: RxFifoFull[1] = func; break;
        case CallbackId::kSleepAck: SleepCallback = func; break;
        case CallbackId::kWakeUp: WakeUpCallback = func; break;
        case CallbackId::kError: ErrorCallback = func; break;
    }
}

void Can::SetOperatingMode(OperatingMode mode) {
    using OM = OperatingMode;
    
    auto OperateSleepMode = [&]() {
        CAN->MCR.SLEEP = 1;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.SLAK == 0); });
    }; 
    
    auto OperateInitMode = [&]() {
        CAN->MCR.SLEEP = 0;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.SLAK == 1); });
        CAN->MCR.INRQ = 1;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.INAK == 0); });
    };
    
    auto OperateNormalMode = [&]() {
        // util::BusyWait<constant::TimeOut::kCan>(IsTimeOut);
        CAN->MCR.SLEEP = 0;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.SLAK == 1); });

        // Exit Initialization mode
        CAN->MCR.INRQ = 0;
        util::BusyWait<constant::TimeOut::kCan>([&](){ return (CAN->MSR.INAK == 1); });
    };

    switch (mode) {
        case OM::kSleep:          OperateSleepMode();   return;
        case OM::kInitialization: OperateInitMode();    return;
        case OM::kNormal:         OperateNormalMode();  return;
        default: /* TODO(@abadr99): Support Unreachable code */ break;
    }
}

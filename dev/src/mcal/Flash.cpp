/**
 * @file Flash.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Util.h"
#include "utils/BitManipulation.h"
#include "utils/Constant.h"
#include "mcal/Flash.h"

using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::constant;
using namespace stm32::registers::flash;
using namespace stm32::dev::mcal::flash;

FlashTypeDef conf;  // Flash configuration structure under interruption
volatile FlashRegDef* Flash::FLASH = nullptr;
typename Flash::pFunction Flash::ErrorCodeCallback = nullptr;
typename Flash::pFunction Flash::EndOfOperationCallback = nullptr;
void Flash::Init() {
    FLASH = reinterpret_cast<volatile FlashRegDef*>(Addr<Peripheral::kFLASH>::Get());
}

Status Flash::Program(FlashTypeDef* pflash, TypeProgram prog, uint32_t address, uint64_t data) {
    Status status = Status::kError;
    uint8_t niteration = 0;
    if (pflash->lockState == LockState::kLocked) {
        return Status::kBusy;
    } else {
        pflash->lockState = LockState::kLocked;
    }
    status = WaitForLastOperation();
    if (status == Status::kOK) {
        if (prog == TypeProgram::kHalfWord) {
            niteration = 1;
        } else if (prog == TypeProgram::kWord) {
            niteration = 2;
        } else if (prog == TypeProgram::kDoubleWord) {
            niteration = 4;
        }
        for (uint8_t ind = 0; ind < niteration; ++ind) {
            ProgramHalfWord(*pflash, (address + (2*ind)), static_cast<uint16_t>(data >> (16*ind)));
            status = WaitForLastOperation();
            FLASH->CR.PG = 0;  // Disable programming
            if (status != kOK) break;
        }
    }
    pflash->lockState = LockState::kUnLocked;
    return status;
}
Status Flash::ProgramIT(TypeProgram prog, uint32_t address, uint64_t data) {
    Status status = Status::kOK;
    conf.address = address;
    conf.data = data;
    if (prog == TypeProgram::kHalfWord) {
        conf.type = ProcedureTypeDef::kHalfWordProgram;
        conf.dataremaining = 1;
    } else if (prog == TypeProgram::kWord) {
        conf.type = ProcedureTypeDef::kWordProgram;
        conf.dataremaining = 2;
    } else if (prog == TypeProgram::kDoubleWord) {
        conf.type = ProcedureTypeDef::kDoubleWordProgram;
        conf.dataremaining = 4;
    }
    ProgramHalfWord(conf, conf.address, static_cast<uint16_t>(conf.data));
    return status;
}
void Flash::SetErrorCallback(pFunction func) {
    ErrorCodeCallback = func;
}
typename Flash::pFunction Flash::GetErrorCallback() {
    return ErrorCodeCallback;
}
void Flash::SetEndOfOperationCallback(pFunction func) {
    EndOfOperationCallback = func;
}
typename Flash::pFunction Flash::GetEndOfOperationCallback() {
    return EndOfOperationCallback;
}
extern "C" void FLASH_IRQHandler(void) {
    auto FlashReg = reinterpret_cast<volatile FlashRegDef*>(Addr<Peripheral::kFLASH>::Get());
    uint32_t address = 0;
    if ((FlashReg->SR.PGERR) || (FlashReg->SR.WRPRTERR)) {
        address = conf.address;
        conf.address = 0xFFFFFFFF;  // Reset address
        Flash::GetErrorCallback();
        conf.type = ProcedureTypeDef::kNone;
    }
    if (FlashReg->SR.EOP) {
        FlashReg->SR.EOP = 1;  // Clear EOP flag
        if (conf.type != ProcedureTypeDef::kNone) {
            if (conf.type == ProcedureTypeDef::kPageErase) {
                conf.dataremaining--;
                if (conf.dataremaining != 0) {
                    address = conf.address;
                    Flash::GetEndOfOperationCallback();
                    address = conf.address + 0x400;  // 0x400 is the page size
                    conf.address = address;
                    FlashReg->CR.PER = 0;
                    Flash::PageErase(address);
                } else {
                    conf.address = 0xFFFFFFFF;  // Reset address
                    conf.type = ProcedureTypeDef::kNone;
                    Flash::GetEndOfOperationCallback();
                }
            } else if (conf.type == ProcedureTypeDef::kMassErase) {
                FlashReg->CR.MER = 0;
                Flash::GetEndOfOperationCallback();
                conf.type = ProcedureTypeDef::kNone;
            } else {
                conf.dataremaining--;
                if (conf.dataremaining != 0) {
                    conf.address += 2;
                    address = conf.address;
                    conf.data = (conf.data >> 16);
                    FlashReg->CR.PG = 0;
                    Flash::ProgramHalfWord(conf, address, static_cast<uint16_t>(conf.data));
                } else {
                    Flash::GetEndOfOperationCallback();
                    conf.address = 0xFFFFFFFF;  // Reset address
                    conf.type = ProcedureTypeDef::kNone;
                }
            }
        }
    }
    if (conf.type == ProcedureTypeDef::kNone) {
        FlashReg->CR.PG = 0;
        FlashReg->CR.PER = 0;
        FlashReg->CR.MER = 0;
        FlashReg->CR.ERRIE = 0;
        FlashReg->SR.EOP = 1;
    }
}

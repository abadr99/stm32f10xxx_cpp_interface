/**
 * @file Flash.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2025-05-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Util.h"
#include "utils/BitManipulation.h"
#include "utils/Constant.h"
#include "mcal/Nvic.h"
#include "mcal/Flash.h"

using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::constant;
using namespace stm32::registers::flash;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::flash;

FlashTypeDef conf;  // Flash configuration structure under interruption
constexpr uint32_t kPageSize = 0x400;
volatile FlashRegDef* Flash::FLASH = nullptr;
typename Flash::pFunction Flash::ErrorCodeCallback = nullptr;
typename Flash::pFunction Flash::EndOfOperationCallback = nullptr;
void Flash::Init() {
    FLASH = reinterpret_cast<volatile FlashRegDef*>(Addr<Peripheral::kFLASH>::Get());
}

Status Flash::Program(FlashTypeDef* pflash, TypeProgram prog, uint32_t address, uint64_t data) {
    Status status = Status::kError;
    uint8_t niteration = 0;
    if (FLASH->CR.LOCK == 1) {
        Unlock();
    }
    FLASH->CR.STRT = 0;
    status = WaitForLastOperation(pflash);
    if (status == Status::kOK) {
        if (prog == TypeProgram::kHalfWord) {
            niteration = 1;
        } else if (prog == TypeProgram::kWord) {
            niteration = 2;
        } else if (prog == TypeProgram::kDoubleWord) {
            niteration = 4;
        }
        for (uint8_t ind = 0; ind < niteration; ++ind) {
            ProgramHalfWord(pflash, (address + (2*ind)), static_cast<uint16_t>(data >> (16*ind)));
            status = WaitForLastOperation(pflash);
            FLASH->CR.PG = 0;  // Disable programming
            if (status != Status::kOK) break;
        }
    }
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
    FLASH->CR.ERRIE = 1;
    FLASH->CR.EOPIE = 1;
    FLASH->CR.PG = 1;
    ProgramHalfWord(&conf, conf.address, static_cast<uint16_t>(conf.data));
    return status;
}
Status Flash::Unlock() {
    Status status = Status::kOK;
    if (FLASH->CR.LOCK) {
        FLASH->KEYR = static_cast<uint32_t>(KeyVal::kKEY1);
        FLASH->KEYR = static_cast<uint32_t>(KeyVal::kKEY2);
        if (FLASH->CR.LOCK) {
            status = Status::kError;
        }
    }
    return status;
}
void Flash::Lock() {
    FLASH->CR.LOCK = 1;  // Set the lock bit
}
Status Flash::OBUnlock() {
    if (FLASH->CR.OPTWRE) {
        FLASH->OPTKEYR = static_cast<uint32_t>(KeyVal::kKEY1);
        FLASH->OPTKEYR = static_cast<uint32_t>(KeyVal::kKEY2);
    } else {
        return Status::kError;
    }
    return Status::kOK;
}
void Flash::OBLock() {
    FLASH->CR.OPTWRE = 0;  // Disable option byte write
}
void Flash::OBLaunch() {
    Nvic::Reset();
}
FlashError Flash::GetError(const FlashTypeDef& pflash) {
    return pflash.errorcode;
}
void Flash::ProgramHalfWord(FlashTypeDef *pflash, uint32_t address, uint16_t data) {
    pflash->errorcode = FlashError::kNone;
    FLASH->CR.PG = 1;  // Enable programming
    *(reinterpret_cast<volatile uint16_t*>(address)) = data;  // Program the half-word
}
Status Flash::WaitForLastOperation(FlashTypeDef *pflash) {
    util::BusyWait<constant::TimeOut::kDefault>([&](){ return (FLASH->SR.BSY); });
    if (FLASH->SR.EOP) {
        FLASH->SR.EOP = 1;  // Clear EOP flag
    }
    if (FLASH->SR.WRPRTERR || FLASH->SR.PGERR || FLASH->OBR.OPTERR) {
        SetErrorCode(pflash);
        return Status::kError;
    }
    return Status::kOK;
}
void Flash::PageErase(uint32_t pageaddress) {
    FLASH->CR.PER = 1;
    FLASH->AR = pageaddress;
    FLASH->CR.STRT = 1;
}
void Flash::SetErrorCode(FlashTypeDef *pflash) {
    if (FLASH->SR.WRPRTERR) {
        pflash->errorcode = FlashError::kWRP;
        FLASH->SR.WRPRTERR = 1;  // Clear WRP error flag
    }
    if (FLASH->SR.PGERR) {
        pflash->errorcode = FlashError::kProg;
        FLASH->SR.PGERR = 1;   // Clear programming error flag
    }
    if (FLASH->OBR.OPTERR) {
        pflash->errorcode = FlashError::kOPTV;
        FLASH->OBR.OPTERR = 1;  // Clear option validity error flag
    }
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
                    address = conf.address + kPageSize;  // 0x400 is the page size
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
                    Flash::ProgramHalfWord(&conf, address, static_cast<uint16_t>(conf.data));
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

/**
 * @file Flash.h
 * @author
 * @brief
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef DEV_INC_MCAL_FLASH_H_
#define DEV_INC_MCAL_FLASH_H_

#include "mcal/stm32f103xx.h"
#include "utils/Constant.h"
using namespace stm32::constant;

namespace stm32 {
namespace dev {
namespace mcal {
namespace flash {
enum class ProcedureTypeDef {
    kNone,
    kPageErase,
    kMassErase,
    kHalfWordProgram,
    kWordProgram,
    kDoubleWordProgram,
};
enum class LockState {
    kLocked,
    kUnLocked,
};
enum class FlashError {
    kNone,  //  No error
    kProg,  //  Programming error
    kWRP,   //  Write protection error
    kOPTV,  //  Option validity error
};
enum class TypeProgram {
    kHalfWord = 1,
    kWord,
    kDoubleWord,
};
enum class Latency {
    kLatency0,
    kLatency1,
    kLatency2,
};
enum Status {
    kOK,
    kError,
    kBusy,
    kTimeout,
};
struct FlashTypeDef {
    volatile ProcedureTypeDef type;   // Ongoing procedure or not in IT context
    volatile uint32_t dataremaining;  // Pages/Half-words left in IT context
    volatile uint32_t address;        // Program/Erase address
    volatile uint32_t data;           // data to program 
    volatile LockState lockState;     // locking object
    volatile FlashError errorcode;
};
class Flash {
 public:
    using FlashRegDef = stm32::registers::flash::FlashRegDef;
    using flash_ptr   = stm32::type::RegType<FlashRegDef>::ptr;
    using pFunction = stm32::type::pFunction;

    void Init();
    Status Program(FlashTypeDef* pflash, TypeProgram prog, uint32_t address, uint64_t data);
    Status ProgramIT(TypeProgram prog, uint32_t address, uint64_t data);

    void Lock();
    void Unlock();
    void OBLock();
    void OBUnlock();
    void OBLaunch();
    
    uint32_t GetError();

    static void SetErrorCallback(pFunction func);
    static pFunction GetErrorCallback();
    static void SetEndOfOperationCallback(pFunction func);
    static pFunction GetEndOfOperationCallback();
    static void PageErase(uint32_t pageaddress);
    static void ProgramHalfWord(const FlashTypeDef& pflash, uint32_t address, uint16_t data);
    
 private:
    static flash_ptr FLASH;
    static pFunction ErrorCodeCallback;
    static pFunction EndOfOperationCallback;
    void EndOfOperation(uint32_t returnValue);
    void OperationError(uint32_t returnValue);

    Status WaitForLastOperation(uint32_t timeout = TimeOut::kDefault);
};
}  // namespace flash
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_MCAL_FLASH_H_

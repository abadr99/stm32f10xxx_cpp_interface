/**
 * @file Flash.h
 * @author
 * @brief
 * @version 0.1
 * @date 2025-05-08
 * 
 * @copyright Copyright (c) 2025
 * 
 * This file defines an abstraction layer for FLASH memory control on STM32F1 series.
 * It supports polling and interrupt-based programming, page and mass erase, option bytes handling, and error reporting.
 * 
 * References:
 * -STM32F103xx Reference Manual RM0008
 * -STM32F103xx Flash Programming Manual PM0075
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
/**
 * @brief Enumeration for FLASH procedure types
 */
enum class ProcedureTypeDef : uint8_t {
    kNone,               /**< No ongoing procedure */
    kPageErase,          /**< Page erase */
    kMassErase,          /**< Mass erase */
    kHalfWordProgram,    /**< Half-word program */
    kWordProgram,        /**< Word program */
    kDoubleWordProgram,  /**< Double-word program */
};
/**
 * @brief Enumeration for FLASH lock states
 */
enum class LockState : uint8_t {
    kLocked,
    kUnLocked,
};
/**
 * @brief Enumeration for FLASH error codes
 */
enum class FlashError : uint32_t {
    kNone,  /**< No error */
    kProg,  /**<Programming error */
    kWRP,   /**< Write protection error */
    kOPTV,  /**< Option validity error */
};
/**
 * @brief Enumeration for FLASH program types
 */
enum class TypeProgram : uint8_t {
    kHalfWord = 1,
    kWord,
    kDoubleWord,
};
/**
 * @brief Enumeration for FLASH latency settings
 */
enum class Latency : uint8_t {
    kLatency0,  /**< 0 wait state */
    kLatency1,  /** 1 wait state */
    kLatency2,  /** 2 wait states */
};
/**
 * @brief Enumeration for FLASH status
 */
enum class Status : uint8_t {
    kOK,
    kError,
    kBusy,
    kTimeout,
};
/**
 * @brief Enumeration for FLASH key values
 */
enum class KeyVal : uint32_t {
    kRDPRT = 0x00A5,        /**< Read protection key */
    kKEY1 = 0x45670123,     /**< First key value */
    kKEY2 = 0xCDEF89AB,     /**< Second key value */
};
/**
 * @brief Structure for FLASH configuration
 */
struct FlashTypeDef {
    volatile ProcedureTypeDef type;     /**< Current procedure type */
    volatile uint32_t dataremaining;    /**< Remaining data to be programmed */
    volatile uint32_t address;          /**< Address to be programmed */
    volatile uint32_t data;             /**< Data to be programmed */
    volatile LockState lockState;       /**< Lock state of the FLASH */
    volatile FlashError errorcode;      /**< Error code */
};
/**
 * @brief Class for FLASH memory control
 * @note For write and erase operations on the Flash memory (write/erase), the internal RC oscillator
        (HSI) must be ON.
 */
class Flash {
 public:
    using FlashRegDef = stm32::registers::flash::FlashRegDef;
    using flash_ptr   = stm32::type::RegType<FlashRegDef>::ptr;
    using pFunction = stm32::type::pFunction;
    /**
     * @brief Initializes the FLASH controller
     */
    void Init();
    /**
     * @brief Programs FLASH memory
     * @param pflash Pointer to FLASH configuration structure
     * @param prog Type of programming (half-word, word, double-word)
     * @param address Address to be programmed
     * @param data Data to be programmed
     * @return Status of the operation
     */
    Status Program(FlashTypeDef* pflash, TypeProgram prog, uint32_t address, uint64_t data);
    /**
     * @brief Programs FLASH memory using interrupts
     * @param prog Type of programming (half-word, word, double-word)
     * @param address Address to be programmed
     * @param data Data to be programmed
     * @return Status of the operation
     */
    Status ProgramIT(TypeProgram prog, uint32_t address, uint64_t data);

    /**
     * @brief Locks the FLASH memory for programming
     * @note This function should be called after programming is complete to prevent accidental writes.
     */
    void Lock();
    /**
     * @brief Locks the Option Byte FLASH memory
     */
    void OBLock();
    /**
     * @brief Unlocks the FLASH memory for programming
     * @return Status of the operation
     * @note This function should be called before programming to allow write access.
     */
    Status Unlock();
    /**
     * @brief Unlocks the Option Byte FLASH memory
     * @return Status of the operation
     */
    Status OBUnlock();
    /**
     * @brief Launches the option byte programming process
     */
    void OBLaunch();
    
    /**
     * @brief Gets the current error code from FLASH context
     * @param pflash Reference to FLASH context structure
     * @return FlashError Enum representing the last error
     */
    FlashError GetError(const FlashTypeDef& pflash);
    /**
     * @brief Sets the error callback function
     * @param func Pointer to the error callback function
     */
    static void SetErrorCallback(pFunction func);
    /**
     * @brief Sets the end of operation callback function
     * @param func Pointer to the end of operation callback function
     * @note The End of write operation (programming or erasing) can trigger an interrupt. This interrupt
             can be used to exit from WFI mode, only if the FLITF clock is enabled. Otherwise, the
             interrupt is served only after an exit from WFI.
     */
    static void SetEndOfOperationCallback(pFunction func);

    /**< These Functions for ISR Handler > **/
    /**
     * @brief Gets the error callback function
     * @return Pointer to the error callback function
     */
    static pFunction GetErrorCallback();
    /**
     * @brief Gets the end of operation callback function
     * @return Pointer to the end of operation callback function
     */
    static pFunction GetEndOfOperationCallback();
    /**
     * @brief Performs a page erase at the specified address
     * @param pageaddress Address of the page to erase
     */
    static void PageErase(uint32_t pageaddress);
    /**
     * @brief Programs a half-word at the specified address
     * @param pflash Pointer to FLASH context structure
     * @param address Target address
     * @param data 16-bit data to be programmed
     */
    static void ProgramHalfWord(FlashTypeDef *pflash, uint32_t address, uint16_t data);
    
 private:
    static flash_ptr FLASH;                      /**< Pointer to FLASH registers */
    static pFunction ErrorCodeCallback;          /**< Error callback function */
    static pFunction EndOfOperationCallback;     /**< End of operation callback function */
     /**
     * @brief Sets the error code in the FLASH context
     * @param pflash Pointer to FLASH context structure
     */
    static void SetErrorCode(FlashTypeDef *pflash);
    /**
     * @brief Waits for the last operation to complete
     * @param pflash Pointer to FLASH context structure
     * @return Status of the operation
     */
    Status WaitForLastOperation(FlashTypeDef *pflash);
};
}  // namespace flash
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_MCAL_FLASH_H_

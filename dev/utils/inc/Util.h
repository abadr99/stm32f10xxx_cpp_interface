/**
 * @file Util.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_UTILS_INC_UTIL_H_
#define DEV_UTILS_INC_UTIL_H_

#include "Rcc.h"
#include "Pin.h"

namespace stm32 {
namespace utils {
    
    inline stm32::dev::mcal::rcc::Peripheral 
    MapPortToPeripheral(stm32::dev::mcal::pin::Port port) {
        using Peripheral = stm32::dev::mcal::rcc::Peripheral; 
        using Port       = stm32::dev::mcal::pin::Port; 
        switch (port) {
            case Port::kPortA:    return Peripheral::kIOPA;
            case Port::kPortB:    return Peripheral::kIOPB;
            case Port::kPortC:    return Peripheral::kIOPC;
        }
        STM32_ASSERT(1);
        return Peripheral::kUnknown;
    }

}   // namespace utils
}   // namespace stm32

#endif  // DEV_UTILS_INC_UTIL_H_
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

#ifndef DEV_INC_UTILS_UTIL_H_
#define DEV_INC_UTILS_UTIL_H_

#include <functional>

#include "utils/Assert.h"
#include "mcal/Rcc.h"
#include "mcal/Pin.h"
#include "utils/Constant.h"

namespace stm32 {
namespace util {
    
    using stm32::dev::mcal::rcc::Peripheral; 
    using stm32::dev::mcal::pin::Port; 
    using stm32::constant::TimeOut;
    
    inline Peripheral MapPortToPeripheral(Port port) {
        switch (port) {
            case Port::kPortA:    return Peripheral::kIOPA;
            case Port::kPortB:    return Peripheral::kIOPB;
            case Port::kPortC:    return Peripheral::kIOPC;
        }
        STM32_ASSERT(0);
        return Peripheral::kUnknown;
    }
    
    using Func = std::function<bool()>;
    template <int timeout = TimeOut::kDefault>
    void BusyWait(const Func& cond) {
        uint32_t i = 0;
        for (; cond() && i != timeout; ++i) {}
        if (i >= timeout) {
            STM32_ASSERT(0);
        }
    }

}   // namespace util
}   // namespace stm32

#endif  // DEV_INC_UTILS_UTIL_H_

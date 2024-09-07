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

#include "Assert.h"
#include "Rcc.h"
#include "Pin.h"
#include "Constant.h"
#include <functional>
namespace stm32 {
namespace util {
    
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
    
    using Func = std::function<bool()>;
    template <int timeout = stm32::constant::TimeOut::kDefault>
    void BusyWait(const Func& cond) {
        for (int i = 0; cond() && i != timeout; ++i) {}
    }

}   // namespace util
}   // namespace stm32

#endif  // DEV_UTILS_INC_UTIL_H_

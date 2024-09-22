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

#define UTILS_EMPTY_MESSAGE  ""
#include "utils/Assert.h"
#include "mcal/Rcc.h"
#include "mcal/Pin.h"
#include "utils/Constant.h"

namespace stm32 {
namespace util {
namespace helpers {

inline void IntToString(int num, char *str) {
    int index = 0;
    int  negFlag = 0;
    // Handle the case when the number is 0
    if (num == 0) {
        str[index++] = '0';
        str[index] = '\0';
        return;
    }   
    // Handle the case when the number is negative
    if (num < 0) {
        num *= -1;
        str[index++] = '-';
        negFlag = 1;
    }

    // Process each digit of the number
    while (num != 0) {
        str[index] = (num % 10) + '0';  //  Convert digit to character
        num /= 10;  //   Remove the processed digit
        index++;
    }
    str[index] = '\0';  //  Null-terminate the string

    //  Reverse the string to get the correct order
    for (int i = negFlag; i < index / 2; i++) {
        char temp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = temp;
    }
}

}  // namespace helpers
    using stm32::dev::mcal::rcc::Peripheral; 
    using stm32::dev::mcal::pin::Port; 
    using stm32::constant::TimeOut;
    
    inline Peripheral MapPortToPeripheral(Port port) {
        switch (port) {
            case Port::kPortA:    return Peripheral::kIOPA;
            case Port::kPortB:    return Peripheral::kIOPB;
            case Port::kPortC:    return Peripheral::kIOPC;
        }
        STM32_ASSERT(0, UTILS_EMPTY_MESSAGE);
        return Peripheral::kUnknown;
    }
    
    using Func = std::function<bool()>;
    template <int timeout = TimeOut::kDefault>
    void BusyWait(const Func& cond) {
        uint32_t i = 0;
        for (; cond() && i != timeout; ++i) {}
        if (i >= timeout) {
            STM32_ASSERT(0, UTILS_EMPTY_MESSAGE);
        }
    }

}   // namespace util
}   // namespace stm32

#endif  // DEV_INC_UTILS_UTIL_H_

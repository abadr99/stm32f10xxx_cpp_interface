/**
 * @file Types.h
 * @brief 
 * @version 0.1
 * @date 2024-03-11
 * 
 * @copyright Copyright (c) 2024
 * @todo: This file should be in common directory 
 */

#ifndef DEV_UTILS_INC_TYPES_H_
#define DEV_UTILS_INC_TYPES_H_

#include <stdint.h>

namespace stm32 {
namespace type {
#define CONV_TO_STRING(str_)  #str_

#define CONFIG_ERROR(peripheral_, error_) \
    CONV_TO_STRING(Invalid ## peripheral_ ## error_)
template<typename T>
using RegWidth = T;

using pFunction = void(*)();
using bit = bool;

enum DigitalVoltage { 
    kLow, 
    kHigh 
};

enum class ConnectionType {
    kForward_Bias,
    kReverse_Bias,
};

}  // namespace type
}  // namespace stm32

#endif  //  DEV_UTILS_INC_TYPES_H_

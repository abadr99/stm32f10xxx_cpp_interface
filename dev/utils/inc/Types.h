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

#define INSTANTIATE_CONNECTION_CLASS(clazz)\
    template class clazz<ConnectionType::kForward_Bias>;\
    template class clazz<ConnectionType::kReverse_Bias>;

#define F_CPU (8000000U)

}  // namespace type
}  // namespace stm32

#endif  //  DEV_UTILS_INC_TYPES_H_

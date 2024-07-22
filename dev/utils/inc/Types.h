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
namespace utils {
namespace types {

using IO = volatile uint32_t;
using RegWidth_t = uint32_t;
using pFunction = void(*)();
#define F_CPU (8000000U)

}  // namespace types
}  // namespace utils
}  // namespace stm32

#endif  //  DEV_UTILS_INC_TYPES_H_

/**
 * @file Constant.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-09-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_UTILS_CONSTANT_H_
#define DEV_INC_UTILS_CONSTANT_H_

#include "utils/Types.h"
using namespace stm32::type;

namespace stm32 {
namespace constant {

static constexpr uint32_t kCpuFreq = 8000000U;

template <ConnectionType CT>
struct DigitalState {};

template <>
struct DigitalState<ConnectionType::kForward_Bias> {
    static constexpr DigitalVoltage kActiveVoltage   = kHigh;
    static constexpr DigitalVoltage kInActiveVoltage = kLow;
};

template <>
struct DigitalState<ConnectionType::kReverse_Bias> {
    static constexpr DigitalVoltage kActiveVoltage   = kLow;
    static constexpr DigitalVoltage kInActiveVoltage = kHigh;
};

struct TimeOut {
    static constexpr uint32_t kDefault = 5000UL;
    static constexpr uint32_t kUsart   = 2000UL;
    static constexpr uint32_t kSdCard  = 200UL;
    static constexpr uint32_t kRcc     = 400UL;
    static constexpr uint32_t kRtc     = 1000UL;
    static constexpr uint32_t kSpi     = 400UL;
};

}  // namespace constant
}  // namespace stm32


#endif  // DEV_INC_UTILS_CONSTANT_H_


/**
 * @file BitManipulation.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_UTILS_INC_BITMANIPULATION_H_
#define DEV_UTILS_INC_BITMANIPULATION_H_

#include <stdint.h>

namespace stm32 {
namespace dev {
namespace utils {
namespace bit_manipulation {

template<typename T>
inline constexpr T GetAllOnes() {
    return static_cast<T>(-1);
}

// Return specific number of ones
// Example: GetOnes(4) --> 0b1111
template<typename T>
inline constexpr T GetOnes(const T NumberOfOnes) {
    return (1 << NumberOfOnes) - 1;
}

template<typename T, uint8_t startBit, uint8_t endBit = startBit>
constexpr T ExtractBits(const T value) {
    static_assert(startBit <= endBit,
                  "Calling ExtractBits with startBit first");
    uint8_t numberOfBits = endBit - startBit + 1;
    return (value >> startBit) & (utils::GetOnes<uint8_t>(numberOfBits));
}

}  // namespace bit_manipulation
}  // namespace utils
}  // namespace dev
}  // namespace stm32

#endif  // DEV_UTILS_INC_BITMANIPULATION_H_

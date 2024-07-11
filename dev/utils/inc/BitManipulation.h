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
#include <assert.h>
namespace stm32 {
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
    return (sizeof(T) * 8) == NumberOfOnes ? GetAllOnes<T>()
                                           : (1 << NumberOfOnes) - 1;
}

template<typename T, uint8_t startBit, uint8_t endBit = startBit>
constexpr T ExtractBits(const T value) {
    static_assert(startBit <= endBit,
                  "Calling ExtractBits with startBit first");
    uint8_t numberOfBits = endBit - startBit + 1;
    return (value >> startBit) & (GetOnes<T>(numberOfBits));
}

template<typename T, uint8_t TStart, uint8_t TEnd = TStart>
inline constexpr T WriteBits(T container, T val) {
    static_assert(TStart <= TEnd, "Calling WriteBits with startBit first");
    static_assert(TEnd < sizeof(T) * 8, "TEnd is out of bounds for type T");
    T ones = GetOnes<T>(static_cast<T>(TEnd - TStart) + 1);
    T mask = ~(ones << TStart);
    return (container & mask) | (val << TStart);
}
template<typename T>
inline constexpr T WriteBits(uint8_t start, uint8_t end , T container, T val) {  // NOLINT [whitespace/line_length]
    assert(start <= end && "Calling WriteBits with startBit first");
    T ones = GetOnes<T>(static_cast<T>(end - start) + 1);
    T mask = ~(ones << start);
    return (container & mask) | (val << start);
}
template<typename T, uint8_t TStart, uint8_t TEnd = TStart>
inline constexpr T  SetBits(T container) {
    static_assert(TStart <= TEnd, "Calling SetBits with startBit > endBit");
    static_assert(TEnd < sizeof(T) * 8, "TEnd is out of bounds for type T");
    T ones = GetOnes<T>(static_cast<T>(TEnd - TStart) + 1);
    T mask = ones << TStart;
    return container | mask;
}
template<typename T, uint8_t TStart, uint8_t TEnd = TStart>
inline constexpr T  ClearBits(T container) {
    static_assert(TStart <= TEnd, "Calling ClearBits with startBit > endBit");
    static_assert(TEnd < sizeof(T) * 8, "TEnd is out of bounds for type T");
    T ones = GetOnes<T>(static_cast<T>(TEnd - TStart) + 1);
    T mask = ~(ones << TStart);
    return container & mask;
}
}  // namespace bit_manipulation
}  // namespace utils
}  // namespace stm32

#endif  // DEV_UTILS_INC_BITMANIPULATION_H_

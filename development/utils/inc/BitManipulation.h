#ifndef _BIT_MANIPULATION_H_
#define _BIT_MANIPULATION_H_

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

}}}} // stm32::dev::utils::bit_manipulation

#endif // _BIT_MANIPULATION_H_
/**
 * @file BitSet.h
 * @brief 
 * @version 0.1
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_UTILS_INC_BITSET_H_
#define DEV_UTILS_INC_BITSET_H_

#include "BitManipulation.h"

namespace stm32 {
namespace util {

template <typename T>
class BitSet {
 public:
    using Bit_t = uint8_t;
    explicit BitSet(const T bits) : bits_(bits)
    { }
    template <T FROM, T TO = FROM>
    inline constexpr void SetValue(T val) {
        bits_ = stm32::util::WriteBits<T, FROM, TO>(bits_, val);   // NOLINT [whitespace/end_of_line]
    }

    template <T FROM, T TO = FROM>
    constexpr T GetValue() {
        return stm32::util::ExtractBits<T, FROM, TO>(bits_);
    }

    template <T FROM, T TO = FROM>
    T GetValue() const {
        return stm32::util::ExtractBits<T, FROM, TO>(bits_);
    }
    
    Bit_t operator[](uint8_t idx) {
        return ((bits_ & (1 << idx)) >> idx);
    }

 private:
    T bits_;
};

}   // namespace util
}   // namespace stm32
#endif  // DEV_UTILS_INC_BITSET_H_

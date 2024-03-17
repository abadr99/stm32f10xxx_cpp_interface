/**
 * @file BitSet.h
 * @brief 
 * @version 0.1
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_BITSET_INC_MATH_H_
#define DEV_BITSET_INC_MATH_H_

#include "BitManipulation.h"

namespace stm32 {
namespace utils {
namespace bitset {

template <typename T>
class BitSet {
 public:
    BitSet(const T bits) : bits_(bits)
    { }

    template <T FROM, T TO = FROM>
    inline constexpr void SetValue(T val) {
        bits_ = stm32::utils::bit_manipulation::WriteBits<T, FROM, TO>(bits_, val);
    }
    
    template <T FROM, T TO = FROM>
    constexpr T GetValue() {
        return stm32::utils::bit_manipulation::ExtractBits<T, FROM, TO>(bits_);
    }

    T operator[](T idx) {
        return ((bits_ & (1<<idx))>>idx);
    }

 private:
    T bits_;
};

}   // namespace bitset
}   // namespace utils
}   // namespace stm32

#endif // DEV_BITSET_INC_MATH_H_
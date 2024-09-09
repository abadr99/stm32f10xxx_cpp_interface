/**
 * @file Array.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_UTILS_INC_ARRAY_H_
#define DEV_UTILS_INC_ARRAY_H_

#include <cstddef>

namespace stm32 {
namespace util {
template<typename T, std::size_t kSize>
class Array {
 public:
    Array() = default;
    Array(const Array& other) {
        assert(other.Size() == kSize);
        for (size_t idx = 0 ; idx < kSize ; ++idx) {
            arr_[idx] = other[idx];
        }
    }
    std::size_t Size() const {
        return kSize;
    }
    T& operator[](std::size_t index) {
        return arr_[index];
    }
    T operator[](std::size_t index) const {
        return arr_[index];
    }
    bool operator==(const Array& other) {
        assert(other.Size() == kSize);
        for (size_t idx = 0 ; idx < kSize ; ++idx) {
            if (arr_[idx] != other[idx]) {
                return false;
            }
        }
        return true;
    }
    Array& operator=(const Array& other) {
        assert(other.Size() == kSize);
        for (size_t idx = 0 ; idx < kSize ; ++idx) {
            arr_[idx] = other[idx];
        }
        return *this;
    }
    
 private:
    T arr_[kSize];
};

}  // namespace util
}  // namespace stm32

#endif  // DEV_UTILS_INC_ARRAY_H_

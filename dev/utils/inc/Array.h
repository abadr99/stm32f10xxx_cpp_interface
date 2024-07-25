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

#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstddef>

namespace stm32 {
namespace utils {
namespace array {

template<typename T, std::size_t size>
class Array {
public:
    Array() = default;
    Array(const Array& other) {
        assert(other.Size() == size);
        for (size_t idx = 0 ; idx < size ; ++idx) {
            arr_[idx] = other[idx];
        }
    }
    std::size_t Size() const {
        return size;
    }
    T& operator[](std::size_t index) {
        return arr_[index];
    }
    T operator[](std::size_t index) const {
        return arr_[index];
    }
    bool operator==(const Array& other) {
        assert(other.Size() == size);
        for (size_t idx = 0 ; idx < size ; ++idx) {
            if (arr_[idx] != other[idx]) {
                return false;
            }
        }
        return true;
    }
    Array& operator=(const Array& other) {
        assert(other.Size() == size);
        for (size_t idx = 0 ; idx < size ; ++idx) {
            arr_[idx] = other[idx];
        }
        return *this;
    }
private:
    T arr_[size];
};

}  // namespace array
}  // namespace utils
}  // namespace stm32

#endif // ARRAY_H_
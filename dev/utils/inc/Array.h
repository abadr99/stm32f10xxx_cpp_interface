/**
 * @file Array.h
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
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
    Array(const Array& other);
    std::size_t Size();
    T& operator[](std::size_t index);
    bool operator==(const Array& other);
    Array& operator=(const Array& other);
private:
    T arr_[size];
};

}  // namespace array
}  // namespace utils
}  // namespace stm32

#endif // ARRAY_H_
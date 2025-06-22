/**
 * @file String.h
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2025-06-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DEV_INC_UTILS_STRING_H_
#define DEV_INC_UTILS_STRING_H_

#include "Types.h"

namespace stm32 {
namespace util {

class String {
    uint32_t size_;
    uint32_t capacity_;
    char *str_;

 public:
    //-- Default Ctor
    String():size_{0}, capacity_{1}, str_{new char[1]} {
        str_[0] = '\0';
    }

    String(const char *str, uint32_t n) : capacity_{n}, str_{new char[n]} {
        size_ = my_strcpy(str_, str);
    }

    explicit String(const char *str) {
        uint32_t i = 0;
        while (str[i] != '\0') {
            i++;
        }
        capacity_ = i+1;
        str_ = new char[capacity_];
        size_  = my_strcpy(str_, str);
    }
    
    //-- Copy constructor
    String(const String &str) {
        size_ = str.size();
        capacity_ = str.capacity();
        str_ = new char[capacity_];
        my_strcpy(str_, str.get());
    }

    char &operator[](uint32_t idx) {
        return str_[idx];
    }

    const char& operator[](uint32_t idx) const {
        return str_[idx];
    }

    String operator+(const String &other) {
        uint32_t new_size = this->size_ + other.size();
        String str("", new_size);
        my_strcpy(str.get(), this->str_);
        my_strcpy(str.get()+this->size_, other.get());
        str.size_ =  new_size;
        str_[new_size] = '\0'; 
        return str;
    }

    void operator+=(const String &other) {
        uint32_t new_size = this->size_+other.size();
        char *new_str = new char[new_size];

        my_strcpy(new_str, this->str_);
        my_strcpy(new_str+this->size_, other.get());

        delete[] str_;
        capacity_ = new_size;
        size_ = capacity_;
        str_ = new_str;
    }

    //-- COpy assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str_;

            size_ = other.size_;
            capacity_ = other.capacity_;
            str_ = new char[capacity_ + 1];  // +1 for '\0'

            my_strcpy(str_, other.str_);
        }
        return *this;
    }
    
    String substr(uint32_t pos = 0, uint32_t len = 0) const {
        if (pos >= size_) {
            return String("", 1);  // return empty
        }

        if (len == 0 || pos + len > size_) {
            len = size_ - pos;  // trim to actual size
        }

        String new_str("", len);
        for (uint32_t i = 0; i < len; ++i) {
            new_str.get()[i] = str_[pos + i];
        }
        new_str.get()[len] = '\0';
        new_str.size_ = len;

        return new_str;
    }

    uint32_t size() const {
        return size_;
    }
    
    uint32_t capacity() const {
        return capacity_;
    }
    
    char* get() const {
        return str_;
    }

 private:
    uint32_t my_strcpy(char *dest, const char *src) {
        uint32_t i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        return i;
    }
};

}  // namespace util
}  // namespace stm32


#endif  // DEV_INC_UTILS_STRING_H_

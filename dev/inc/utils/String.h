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
namespace stm32 {
namespace util {

class String {
    int size_;
    int capacity_;
    char *str_;

 public:
    //-- Default Ctor
    String():size_{0}, capacity_{1}, str_{new char[1]} {
        str_[0] = '\0';
    }

    String(const char *str, int n) : capacity_{n}, str_{new char[n]} {
        size_ = my_strcpy(str_, str);
    }

    explicit String(const char *str) {
        int i = 0;
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

    char operator[](int idx) {
        if (idx < size_) {
            return str_[idx];
        } else {
            return '\0';
        }
    }

    String operator+(const String &other) {
        int new_size = this->size_ + other.size();
        String str("", new_size);
        my_strcpy(str.get(), this->str_);
        my_strcpy(str.get()+this->size_, other.get());
        str.size_ =  new_size;
        str_[new_size] = '\0'; 
        return str;
    }

    void operator+=(const String &other) {
        int new_size = this->size_+other.size();
        char *new_str = new char[new_size];

        my_strcpy(new_str, this->str_);
        my_strcpy(new_str+this->size_, other.get());

        delete[] str_;
        capacity_ = new_size;
        size_ = capacity_;
        str_ = new_str;
    }

    int size() const {
        return size_;
    }
    
    int capacity() const {
        return capacity_;
    }
    
    char* get() const {
        return str_;
    }
    
 private:
    int my_strcpy(char *dest, const char *src) {
        int i = 0;
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

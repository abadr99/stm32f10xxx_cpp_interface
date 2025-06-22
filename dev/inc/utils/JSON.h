/**
 * @file JSON.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DEV_INC_UTILS_JSON_H_
#define DEV_INC_UTILS_JSON_H_

#include "String.h"
#include "Types.h"

using namespace stm32::util;
namespace stm32 {
namespace util {
class JsonUtil {
    String str_;
    uint32_t size_;
    
 public:
    JsonUtil() : str_{}, size_{0} {
    }
    void add(const String& key, const String& value) {
    if (size_ >= 1) {
            str_+= String(",");
    }
        String str(String("\"") + key + String("\": \"") + value + String("\""));
        str_+=str;
        size_++;
    }
    
    String build() const {
        String json = String("{");
        json+=str_;
        json += String("}");
        return json;
    }

    void parse(const String& json, void (*pFun)(String, String)) {
        uint32_t i = 0;
        while (i < json.size()) {
            if (json[i] == '\"') {
                uint32_t keyStart = ++i;
                while (i < json.size() && json[i] != '\"') {
                    i++;
                }
                String key = json.substr(keyStart, i - keyStart);
                i += 2;  // Skip over the closing quote and the colon
                String value;
                if (json[i] == '\"') {
                    uint32_t valueStart = ++i;
                    while (i < json.size() && json[i] != '\"') {
                        i++;
                    }
                    value = json.substr(valueStart, i - valueStart);
                    i++;  // Skip over the closing quote
                } else {
                    uint32_t valueStart = i;
                    while (i < json.size() && json[i] != ',' && json[i] != '}') {
                        i++;
                    }
                    value = json.substr(valueStart, i - valueStart);
                }
                pFun(key, value);
            } else {
                i++;  // Skip over any non-quote characters 
            }
        }
    }
};

}   // namespace util
}   // namespace stm32
#endif  // DEV_INC_UTILS_JSON_H_

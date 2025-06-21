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

#include <map>
#include <string>
#include <cstring>
#include <vector>

namespace stm32 {
namespace util {
class JsonUtil {
 public:
    void add(const std::string& key, const std::string& value) {
        entries.push_back("\"" + key + "\": \"" + value + "\"");
    }
    void add(const std::string& key, int value) {
        entries.push_back("\"" + key + "\": " + std::to_string(value));
    }
    std::string build() const {
        std::string json = "{";
        for (size_t i = 0; i < entries.size(); ++i) {
            json += entries[i];
            if (i != entries.size() - 1) {
                json += ", ";
            }
        }
        json += "}";
        return json;
    }
    static std::map<std::string, std::string> parse(const std::string& json) {
        std::map<std::string, std::string> result;
        size_t i = 0;
        while (i < json.size()) {
            if (json[i] == '\"') {
                size_t keyStart = ++i;
                while (i < json.size() && json[i] != '\"') {
                    i++;
                }
                std::string key = json.substr(keyStart, i - keyStart);
                i += 2;  // Skip over the closing quote and the colon
                std ::string value;
                if (json[i] == '\"') {
                    size_t valueStart = ++i;
                    while (i < json.size() && json[i] != '\"') {
                        i++;
                    }
                    value = json.substr(valueStart, i - valueStart);
                    i++;  // Skip over the closing quote
                } else {
                    size_t valueStart = i;
                    while (i < json.size() && json[i] != ',' && json[i] != '}') {
                        i++;
                    }
                    value = json.substr(valueStart, i - valueStart);
                }
                result[key] = value;
            } else {
                i++;  // Skip over any non-quote characters 
            }
        }
        return result;
    }

 private:
    std::vector<std::string> entries;
};
}   // namespace util
}   // namespace stm32
#endif  // DEV_INC_UTILS_JSON_H_

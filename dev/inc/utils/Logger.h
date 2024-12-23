/**
 * @file Logger.h
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-08-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_UTILS_LOGGER_H_
#define DEV_INC_UTILS_LOGGER_H_

#include "mcal/Usart.h"

using namespace stm32::dev::mcal::usart;

namespace stm32 {
namespace utils {
namespace logger {

class Logger {
 public:
    static void Init(void);
    static void Info(const char *str);
    static void Print(const char *str);
    static void Error(const char *str);
    static void Warning(const char *str);

 private:
    static void Send(const char *str);
    static UsartConfig usartConfig_;
    static Usart usart_;
};
}  // namespace logger
}  // namespace utils
}  // namespace stm32

#endif  // DEV_INC_UTILS_LOGGER_H_

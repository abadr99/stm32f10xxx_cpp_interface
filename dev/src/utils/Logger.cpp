/**
 * @file Logger.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-08-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "utils/Types.h"
#include "utils/Logger.h"
#include "mcal/Usart.h"

using namespace stm32::dev::mcal::usart;
using namespace stm32::utils::logger;

#ifndef LOGGER_USART
#define LOGGER_USART (kUsart1)
#endif

#ifndef LOGGER_BAUD_RATE
#define LOGGER_BAUD_RATE (9600)
#endif

#define INFO_MESSAGE     "[Info]: "
#define ERROR_MESSAGE    "[Error]: "
#define WARNING_MESSAGE  "[Warning]: "

UsartConfig Logger::usartConfig_ = {
    .number = LOGGER_USART,
    .mode = kRxTx,
    .numOfSB = kSb_1_,
    .dataBits = kDataBits_8_,
    .parityMode = kNo_Parity,
    .flowControlState = kNone,
    .baudRate = LOGGER_BAUD_RATE };

Usart Logger::usart_(Logger::usartConfig_);

void Logger::Init(void) {
    Logger::usart_.Init();
}

void Logger::Info(const char *str) {
    Logger::Send(INFO_MESSAGE);
    Logger::Send(str);
}

void Logger::Print(const char *str) {
    Logger::Send(str);
}

void Logger::Error(const char *str) {
    Logger::Send(ERROR_MESSAGE);
    Logger::Send(str);
}

void Logger::Warning(const char *str) {
    Logger::Send(WARNING_MESSAGE);
    Logger::Send(str);
}

void Logger::Send(const char *str) {
    uint32_t str_idx = 0;
    while (str[str_idx] != '\0') {
        usart_.Transmit(str[str_idx++]);
    }
}

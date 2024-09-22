/**
 * @file Esp.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// #include <cstring>
// #include <string>
#include "utils/Util.h"
#include "mcal/Rcc.h"
#include "utils/Assert.h"
#include "mcal/Usart.h"
#include "hal/Esp.h"

#define ESP_BAUD_RATE  (115200)

static constexpr const char* commandStrings[] = {
    "AT\r\n",    
    "AT+RST\r\n",   
    "ATE",
    "AT+CWMODE",
    "AT+CWJAP_CUR",
    "AT+CIPSTART",
    "=",
    "?",
    "\r\n",
    ","
};

#define TCP "TCP"
#define UDP "UDP"
using namespace stm32::util::helpers;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::hal::esp;


Esp::Esp(const UsartNum &usartNum) 
:usartConfig_ {
        usartConfig_.number = usartNum,
        usartConfig_.mode = kRxTx,
        usartConfig_.numOfSB = kSb_1_,
        usartConfig_.dataBits = kDataBits_8_,
        usartConfig_.parityMode = kNo_Parity,
        usartConfig_.flowControlState = kNone,
        usartConfig_.baudRate = ESP_BAUD_RATE },
    usart_(usartConfig_) {
        switch (usartNum) { 
        case kUsart1: 
            Rcc::Enable(Peripheral::kUSART1); 
            break; 
        case kUsart2: 
            Rcc::Enable(Peripheral::kUSART2); 
            break; 
        case kUsart3: 
            Rcc::Enable(Peripheral::kUSART3); 
            break;         
        }
        usart_.Init();
    }


void Esp::Send(const char* str) {
    uint32_t str_idx = 0;
    while (str[str_idx] != '\0') {
        usart_.Transmit(str[str_idx++]);
    }
}

void Esp::Send(Usart::DataValType n) {
    usart_.Transmit(n);
}

void Esp::SetMode(const EspMode &mode) {    
    this->Send(commandStrings[Commands::AT_CWMODE]);
    this->Send(commandStrings[Commands::kSET_POSTFIX]);
    char cMode = static_cast<uint8_t>(mode) + 48;
    this->Send(cMode);
    this->Send(commandStrings[Commands::kAT_END]);
}

void Esp::SetEchoState(const EchoState &state) {
    this->Send(commandStrings[Commands::ATE]);
    char cState = static_cast<uint8_t>(state) + 48;
    this->Send(cState);
    this->Send(commandStrings[Commands::kAT_END]);
}

void Esp::WiFiConnect(const char* username, const char* pswd) {
    this->Send(commandStrings[Commands::AT_CWJAP_CUR]);
    this->Send(commandStrings[Commands::kSET_POSTFIX]);
    this->Send(username);
    this->Send(commandStrings[Commands::kCOMMA]);
    this->Send(pswd);
    this->Send(commandStrings[Commands::kAT_END]);
}

void Esp::ServerConnect(const char* protocol, const char* ip, uint16_t port) {
    this->Send(commandStrings[Commands::AT_CIPSTART]);
    this->Send(commandStrings[Commands::kSET_POSTFIX]);
    this->Send(protocol);
    this->Send(commandStrings[Commands::kCOMMA]);
    this->Send(ip);
    this->Send(commandStrings[Commands::kCOMMA]);
    char strPort[6] = {0};
    IntToString(port, strPort);
    Send(strPort);
    this->Send(commandStrings[Commands::kAT_END]);
}



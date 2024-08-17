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

#include <string>
#include "Assert.h"
#include "Usart.h"
#include "Esp.h"

#define ESP_BAUD_RATE  (115200)

#define AT_CWMODE     "AT+CWMODE"
#define AT_RST        "AT+RST"
#define AT_CWJAP_CUR  "AT+CWJAP_CUR"
#define ATE           "ATE"  

#define AT_SET_POSTFIX  "="  
#define AT_GET_POSTFIX  "?"
#define AT_END          "\r\n"
#define COMMA           std::string(",")

#define TCP "TCP"
#define UDP "UDP"


#define AT_SET(str)     std::string(str) + std::string(AT_SET_POSTFIX)
#define AT_GET(str)     std::string(str) + std::string(AT_GET_POSTFIX)

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
        usart_.Init();
    }


void Esp::Send(const std::string str) {
    for (auto c : str) {
        Send(c);
    }
}

void Esp::Send(const char c) {
    usart_.Transmit(c);
}

void Esp::SetMode(const EspMode &mode) {
    std::string cmd = std::string(AT_SET(AT_CWMODE))
                     + std::to_string(static_cast<uint32_t>(mode))
                     + std::string(AT_END);
    Send(cmd);
}

void Esp::SetEchoState(const EchoState &state) {
    std::string cmd = std::string(ATE)
                     + std::to_string(static_cast<uint32_t>(state))
                     + std::string(AT_END);
    Send(cmd);
}

void Esp::WiFiConnect(const std::string username, const std::string pswd) {
    std::string cmd = std::string(AT_SET(AT_CWJAP_CUR)) 
                    + username + pswd
                    + std::string(AT_END);
    Send(cmd);              
}

void Esp::ServerConnect(const std::string protocol, const std::string ip, uint16_t port) {
    std::string cmd = std::string(AT_SET(AT_CWJAP_CUR)) 
                    + protocol + COMMA
                    + ip + COMMA
                    + std::to_string(port)
                    + std::string(AT_END);
    Send(cmd); 
}

void Esp::SendHttpRequest(const std::string request) {
    std::string cmd = request + std::string(AT_END);
    Send(cmd);
}


// void Esp::RecvHttpResponse(const std::string response) {
    
// }

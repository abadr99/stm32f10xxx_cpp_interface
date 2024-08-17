/**
 * @file HC05.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string>

#include "Assert.h"

#include "Usart.h"
#include "HC05.h"


#define AT              "AT\r\n"
#define AT_RESET        "AT+RESET\r\n"

#define AT_VERSION      "AT+VERSION"
#define AT_NAME         "AT+NAME"
#define AT_PSWD         "AT+PSWD"
#define AT_ROLE         "AT+ROLE"
#define AT_UART         "AT+UART"
#define AT_INQM         "AT+INQM"
#define AT_BIND         "AT+BIND"
#define AT_INQ          "AT+INQ"

#define AT_SET_POSTFIX  "="  
#define AT_GET_POSTFIX  "?"
#define AT_END          "\r\n"

#define AT_SET(str)     std::string(str) + std::string(AT_SET_POSTFIX)
#define AT_GET(str)     std::string(str) + std::string(AT_GET_POSTFIX)

#define COMMA           std::string(",")

using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::hal::bluetooth;

void HC05::Send(char c) {
    usart_.Transmit(c);
}

void HC05::Send(typename Usart::DataValType n) {
    usart_.Transmit(n);
}

void HC05::Send(const std::string& str) {
    for (auto ch : str) {
        this->Send(ch);
    }
}

typename HC05::Usart::DataValType HC05::Receive() {
    return usart_.Receive();
}

void HC05::Test() {
    static const std::string test = std::string(AT) + std::string(AT_END);
    this->Send(test);
}

void HC05::Reset() {
    static const std::string reset = std::string(AT_RESET) + std::string(AT_END);
    this->Send(reset);
}

void HC05::GetFirmWareVersion() {
    static const std::string version = std::string(AT_GET(AT_VERSION)) + std::string(AT_END);
    this->Send(version);
}


void HC05::SetDeviceName(const std::string& name) {
    static const std::string device = std::string(AT_SET(AT_NAME)) 
                                + name 
                                + std::string(AT_END);
    this->Send(device);
}


void HC05::SetParingPin(const std::string& pin) {
    static const std::string paring_pin = std::string(AT_SET(AT_PSWD)) 
                                    + pin 
                                    + std::string(AT_END);
    this->Send(paring_pin);
}


void HC05::SetDeviceRole(DeviceRole role) {
    static const std::string role_cmd = std::string(AT_SET(AT_ROLE)) 
                                + std::to_string(static_cast<uint32_t>(role))
                                + std::string(AT_END);
    this->Send(role_cmd);
}


void HC05::SetUART(uint32_t baudRate, uint32_t stopBits, uint32_t parity) {               
    static const std::string config = std::string(AT_SET(AT_UART))
                                    + std::to_string(baudRate)
                                    + COMMA
                                    + std::to_string(stopBits)
                                    + COMMA
                                    + std::to_string(parity)
                                    + std::string(AT_END);
    this->Send(config);
}

void HC05::SetInquiryMode(InquiryMode im, 
                            uint32_t maxNumberOfBluetoothDevices, 
                            uint32_t timeout) {
    static const std::string mode = std::string(AT_SET(AT_INQM)) 
                                + std::to_string(static_cast<uint32_t>(im))
                                + COMMA 
                                + std::to_string(maxNumberOfBluetoothDevices) 
                                + COMMA 
                                + std::to_string(timeout) 
                                + std::string(AT_END);
    this->Send(mode);
}

void HC05::SetBindToAddress(const std::string& address) {
    static const std::string address_cmd = std::string(AT_SET(AT_BIND)) 
                                    + address
                                    + std::string(AT_END);
    this->Send(address_cmd);
}

void HC05::InquiryBluetoothDevices() {
    static const std::string inq = std::string(AT_GET(AT_INQ)) 
                                + std::string(AT_END);
    this->Send(inq);
}

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

#define COMMA       std::string(",")

using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::hal::bluetooth;

template <UsartNum N>
HC05<N>::HC05(const usart_t& usart): usart_(usart) { /* EMPTY */}

template <UsartNum N>
void HC05<N>::Send(char c) {
    usart_.Transmit(c);
}

template <UsartNum N>
void HC05<N>::Send(typename usart_t::DataValType n) {
    usart_.Transmit(n);
}

template <UsartNum N>
void HC05<N>::Send(const std::string& str) {
    for (auto ch : str) {
        this->Send(ch);
    }
}

template <UsartNum N>
typename HC05<N>::usart_t::DataValType HC05<N>::Receive() {
    return usart_.Receive();
}

template <UsartNum N>
void HC05<N>::Test() {
    static const std::string test = std::string(AT) + std::string(AT_END);
    this->send(test);
}

template <UsartNum N>
void HC05<N>::Reset() {
    static const std::string reset = std::string(AT_RESET) + std::string(AT_END);
    this->send(reset);
}

template <UsartNum N>
void HC05<N>::GetFirmWareVersion() {
    static const std::string version = std::string(AT_GET(AT_VERSION)) + std::string(AT_END);
    this->send(version);
}

template <UsartNum N>
void HC05<N>::SetDeviceName(const std::string& name) {
    static const std::string device = std::string(AT_SET(AT_NAME)) 
                                + name 
                                + std::string(AT_END);
    this->send(device);
}

template <UsartNum N>
void HC05<N>::SetParingPin(const std::string& pin) {
    static const std::string paring_pin = std::string(AT_SET(AT_PSWD)) 
                                    + pin 
                                    + std::string(AT_END);
    this->send(paring_pin);
}

template <UsartNum N>
void HC05<N>::SetDeviceRole(DeviceRole role) {
    static const std::string role_cmd = std::string(AT_SET(AT_ROLE)) 
                                + std::to_string(static_cast<uint32_t>(role))
                                + std::string(AT_END);
    this->send(role_cmd);
}

template <UsartNum N>
void HC05<N>::SetUART(uint32_t baudRate, uint32_t stopBits, uint32_t parity) {
    STM32_ASSERT(true);
}

template <UsartNum N>
void HC05<N>::SetInquiryMode(InquiryMode im, 
                            uint32_t maxNumberOfBluetoothDevices, 
                            uint32_t timeout) {
    static const std::string mode = std::string(AT_SET(AT_INQM)) 
                                + std::to_string(static_cast<uint32_t>(im))
                                + COMMA 
                                + std::to_string(maxNumberOfBluetoothDevices) 
                                + COMMA 
                                + std::to_string(timeout) 
                                + std::string(AT_END);
    this->send(mode);
}

template <UsartNum N>
void HC05<N>::SetBindToAddress(const std::string& address) {
    static const std::string address_cmd = std::string(AT_SET(AT_BIND)) 
                                    + address
                                    + std::string(AT_END);
    this->send(address_cmd);
}

template <UsartNum N>
void HC05<N>::InquiryBluetoothDevices() {
    static const std::string inq = std::string(AT_GET(AT_INQ)) 
                                + std::string(AT_END);
    this->send(inq);
}

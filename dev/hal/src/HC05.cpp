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

#include <cstring>
#include <string>

#include "Assert.h"

#include "Usart.h"
#include "HC05.h"

static constexpr const char* commandStrings[] = {
    "AT\r\n",            // CMD_AT
    "AT+RESET\r\n",      // CMD_AT_RESET
    "AT+VERSION",        // CMD_AT_VERSION
    "AT+NAME",           // CMD_AT_NAME
    "AT+PSWD",           // CMD_AT_PSWD
    "AT+ROLE",           // CMD_AT_ROLE
    "AT+UART",           // CMD_AT_UART
    "AT+INQM",           // CMD_AT_INQM
    "AT+BIND",           // CMD_AT_BIND
    "AT+INQ",            // CMD_AT_INQ
    "=",                 // CMD_SET_POSTFIX
    "?",                 // CMD_GET_POSTFIX
    "\r\n",              // CMD_END
    ",",                 // CMD_COMMA
};


using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::hal::bluetooth;

HC05::HC05(const Usart& usart) : usart_(usart) {}

void HC05::Send(typename Usart::DataValType n) {
    usart_.Transmit(n);
}

void HC05::Send(const char* str) {
    std::size_t size = std::strlen(str);
    for (uint32_t i = 0 ; i < size ; ++i) {
        usart_.Transmit(str[i]);
    }
}

void HC05::Send(const std::string& str) {
    this->Send(str.c_str());
}

typename HC05::Usart::DataValType HC05::Receive() {
    return usart_.Receive();
}

void HC05::Test() {

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
    this->Send(commandStrings[kAT]);
    this->Send(commandStrings[kAT_END]);
}

void HC05::Reset() {
    this->Send(commandStrings[kAT_RESET]);
    this->Send(commandStrings[kAT_END]);
}

void HC05::GetFirmWareVersion() {
    this->Send(commandStrings[kAT_VERSION]);
    this->Send(commandStrings[kGET_POSTFIX]);
    this->Send(commandStrings[kAT_END]);
}

void HC05::SetDeviceName(const std::string& name) {
    this->Send(commandStrings[kAT_NAME]);
    this->Send(commandStrings[kSET_POSTFIX]);
    this->Send(name);
    this->Send(commandStrings[kAT_END]);
}

void HC05::SetParingPin(const std::string& pin) {
    this->Send(commandStrings[kAT_PSWD]);
    this->Send(commandStrings[kSET_POSTFIX]);
    this->Send(pin);
    this->Send(commandStrings[kAT_END]);
}

void HC05::SetDeviceRole(DeviceRole role) {
    this->Send(commandStrings[kAT_ROLE]);
    this->Send(commandStrings[kSET_POSTFIX]);
    this->Send(std::to_string(static_cast<uint32_t>(role)));
    this->Send(commandStrings[kAT_END]);
}

void HC05::SetUART(uint32_t baudRate, uint32_t stopBits, uint32_t parity) {               
    this->Send(commandStrings[kAT_UART]);
    this->Send(commandStrings[kSET_POSTFIX]);
    this->Send(std::to_string(baudRate));
    this->Send(commandStrings[kCOMMA]);
    this->Send(std::to_string(stopBits));
    this->Send(commandStrings[kCOMMA]);
    this->Send(std::to_string(parity));
    this->Send(commandStrings[kAT_END]);
}

void HC05::SetInquiryMode(InquiryMode im, 
                            uint32_t maxNumberOfBluetoothDevices, 
                            uint32_t timeout) {

    this->Send(commandStrings[kAT_INQM]);
    this->Send(commandStrings[kSET_POSTFIX]);
    this->Send(std::to_string(static_cast<uint32_t>(im)));
    this->Send(commandStrings[kCOMMA]);
    this->Send(std::to_string(maxNumberOfBluetoothDevices));
    this->Send(commandStrings[kCOMMA]);
    this->Send(std::to_string(timeout));
    this->Send(commandStrings[kAT_END]);
}

void HC05::SetBindToAddress(const std::string& address) {
    this->Send(commandStrings[kAT_BIND]);
    this->Send(commandStrings[kSET_POSTFIX]);
    this->Send(address);
    this->Send(commandStrings[kAT_END]);
}

void HC05::InquiryBluetoothDevices() {
    this->Send(commandStrings[kAT_INQ]);
    this->Send(commandStrings[kGET_POSTFIX]);
    this->Send(commandStrings[kAT_END]);
}

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

#include "BitManipulation.h"
#include "Assert.h"
#include "Pin.h"
#include "Gpio.h"
#include "Esp.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::esp;

void Esp::Init(Mode mode) {

}
void Esp::WiFiConnect(const char *pUsername, const char *pPass) {

}
void Esp::ServerConnect(const char *protocol,const char *ip, uint16_t port) {

}
void Esp::SendCustomCommand(const char *command) {
    
}
void Esp::SendHttpRequest(const char *pRequest) {
    
}
void Esp::RecvHttpResponse(const char *pResponse) {
    
}
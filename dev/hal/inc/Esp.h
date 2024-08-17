/**
 * @file Esp.h
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_HAL_INC_ESP_H_
#define DEV_HAL_INC_ESP_H_
#include <string>
using namespace stm32::dev::mcal::usart;
namespace stm32 {
namespace dev {
namespace hal {
namespace esp {

enum class EspMode {
    kSTA = 1,    //  Station Mode
    kAP,         //  Access point Mode
    kSTA_Ap      //  Station Mode + Access point Mode
};

enum class EchoState {
    kOff,
    kOn
};



class Esp {
 public:
    explicit Esp(const UsartNum &usartNum);
    void Init();
    void Send(const std::string str);
    void Send(const char c);
    void SetMode(const EspMode &mode);
    void SetEchoState(const EchoState &state);
    void WiFiConnect(const std::string username, const std::string pswd);
    void ServerConnect(const std::string protocol, const std::string ip, uint16_t port);
    void SendHttpRequest(const std::string request);
    // TODO(@MRefat): Add the implementation of it, implement receive function
    // void RecvHttpResponse(const std::string response);
 private:
    UsartConfig usartConfig_;
    Usart usart_;
};

}   //  namespace esp
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_ESP_H_

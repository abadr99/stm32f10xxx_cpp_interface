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

using namespace stm32::dev::mcal::usart;
namespace stm32 {
namespace dev {
namespace hal {
namespace esp {
namespace helpers {

void Helper_IntToString(int num, char *str);

}
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
    void Send(const char *str);
    void Send(Usart::DataValType n);
    void SetMode(const EspMode &mode);
    void SetEchoState(const EchoState &state);
    void WiFiConnect(const char* username, const char* pswd);
    void ServerConnect(const char* protocol, const char* ip, uint16_t port);

 private:
    enum  Commands {
      kAT,
      kAT_RST,
      ATE,
      AT_CWMODE,
      AT_CWJAP_CUR,
      AT_CIPSTART,
      kSET_POSTFIX,
      kGET_POSTFIX,
      kAT_END,
      kCOMMA
    };
    UsartConfig usartConfig_;
    Usart usart_;
};

}   //  namespace esp
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_ESP_H_

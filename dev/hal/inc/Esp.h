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
#ifndef DEV_HAL_INC_DC_MOTOR_H_
#define DEV_HAL_INC_DC_MOTOR_H_

namespace stm32 {
namespace dev {
namespace hal {
namespace esp {

enum class Mode {
    kSTA = 1,    //  Station Mode
    kAP,         //  Access point Mode
    kSTA_Ap      //  Station Mode + Access point Mode
};
class Esp {
 public:
    void Init(Mode mode);
    void WiFiConnect(const char *pUsername, const char *pPass);
    void ServerConnect(const char *protocol,const char *ip, uint16_t port);
    void SendCustomCommand(const char *command);
    void SendHttpRequest(const char *pRequest);
    void RecvHttpResponse(const char *pResponse);
 private:
};

}   //  namespace esp
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_DC_MOTOR_H_

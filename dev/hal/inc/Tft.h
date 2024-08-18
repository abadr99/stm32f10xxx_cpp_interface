/**
 * @file TFT.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_TFT_H_
#define DEV_HAL_INC_TFT_H_

using namespace stm32::dev::mcal::pin; 

namespace stm32 {
namespace dev {
namespace hal {
namespace tft {
enum TftCommand {
    kSLPOUT = 0x11,     //  Sleep out & booster on
    kCASET  = 0x2A,     //  Column address set
    kRASET  = 0x2B,     //  Row address set
    kRAWMR  = 0x2C      //  Memory write
};
enum Colors {
    kBlack   = 0x0000,
    kBlue    = 0x001F,
    kRed     = 0xF800,
    kMagenta = 0xF81F,
    kGreen   = 0x07E0,
    kCyan    = 0x07FF,
    kYellow  = 0xFFE0,
    kWhite   = 0xFFFF
};
class Tft {
 public:
    Tft(Pin A0, Pin rst);
    void DisplayImage();
    void FillColor();
    void DrawRectangle();
 private:
    Pin A0;
    Pin rst;
    void SendCommand(uint8_t command);
    void SendData(uint8_t data);
};
}   //  namespace tft
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_TFT_H_

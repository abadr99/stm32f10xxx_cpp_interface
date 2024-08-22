/**
 * @file Tft.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_TFT_H_
#define DEV_HAL_INC_TFT_H_
using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::spi;
using namespace stm32::utils::array;
namespace stm32 {
namespace dev {
namespace hal {
namespace tft {
enum TftCommand {
    kSLPOUT   = 0x11,   //  Sleep out & booster on
    kCASET    = 0x2A,   //  Column address set
    kRASET    = 0x2B,   //  Row address set
    kRAWMR    = 0x2C,   //  Memory write
    kCOLMOD   = 0x3A,   //  Interface pixel format
    kCOLMOD_P = 0x05,   //  RGB 5-6-5
    kDISPON   = 0x29    //  Display on
};
enum TftColors {
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
    Tft(Pin A0, Pin rst, Spi SdSpi);
    void DisplayImage(const Array<uint16_t, 20480> image);
    void FillColor(TftColors color);
    void DrawRectangle();
 private:
    const Pin A0;
    const Pin rst;
    Spi TFtSpi;
    void SendCommand(uint8_t command);
    void SendData(uint8_t data);
};
}   //  namespace tft
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_TFT_H_

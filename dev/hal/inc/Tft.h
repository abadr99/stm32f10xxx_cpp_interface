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
using namespace stm32::type;
namespace stm32 {
namespace dev {
namespace hal {
namespace tft {
#define RGB565  0x05
enum TftCommand {
    kSLPOUT   = 0x11,   //  Sleep out & booster on
    kCASET    = 0x2A,   //  Column address set
    kRASET    = 0x2B,   //  Row address set
    kRAWMR    = 0x2C,   //  Memory write
    kCOLMOD   = 0x3A,   //  Interface pixel format
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
enum TftResolution {
    k128x160,   //   Common resolution for small TFT displays
    k240x320,   //   Another common resolution
    k320x480,   //   Larger resolution
    k480x800    //   High-resolution TFT display
};
struct TftConfig {
    Pin A0;
    Pin rst;
    Spi TFtSpi;
    TftResolution resolution;  // TFT display resolution
    uint16_t width;
    uint16_t height;
};
class Tft {
 public:
    explicit Tft(const TftConfig& config);
    void Reset();
    void DisplayImage(const util::Array<uint16_t, 20480> image);
    void DrawRectangle(uint8_t hight, uint8_t width, uint8_t xAxis, uint8_t yAxis, TftColors color);
 private:
    TftConfig config_;
    void SendCommand(uint8_t command);
    void SendData(uint8_t data);
    void SetAddress(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY);
    void SetPixel(uint16_t pixel);
    void DrawHLine(uint8_t xAxis, uint8_t yAxis, uint8_t length, TftColors color);
    void DrawVLine(uint8_t xAxis, uint8_t yAxis, uint8_t length, TftColors color);
    void InitializeResolution();
};
}   //  namespace tft
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_TFT_H_

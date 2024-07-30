/**
 * @file LCD.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_LCD_H_
#define DEV_HAL_INC_LCD_H_

#include <string>
using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
using namespace stm32::utils::array;

enum class LCDCommand : uint8_t {
    kCLEAR_SCREEN               = 0x01,
    kRETURN_HOME                = 0x02,

    kFUNCTION_SET_8_BIT         = 0x38,
    kFUNCTION_SET_4_BIT         = 0x28,

    kDISPLAY_ON_CURSOR_ON       = 0x0E,
    kDISPLAY_ON_CURSOR_OFF      = 0x0C,
    kDISPLAY_OFF_CURSOR_OFF     = 0x09,

    kBLINK_ON                   = 0x0F,
    kBLINK_OFF                  = 0x0E,

    kENTRY_MODE_DEC_SHIFT_OFF   = 0x04,
    kENTRY_MODE_DEC_SHIFT_ON    = 0x05,
    kENTRY_MODE_INC_SHIFT_OFF   = 0x06,
    kENTRY_MODE_INC_SHIFT_ON    = 0x07,

    kSHIFT_LEFT                 = 0x18,
    kSHIFT_RIGHT                = 0x1C,

    kINC_CURSOR                 = 0x04,
    kDEC_CURSOR                 = 0x00,

    kCGRAM_START                = 0x40,
    kDDRAM_START                = 0x80
};
enum LcdMode : uint8_t {
    k8_bit,
    k10_bit,
};
enum LcdNibbles : uint8_t {
    kLowNibble,
    kHighNibble,
};
enum LcdRows : uint8_t {
    kRow1 = 1,
    kRow2,
};
enum LcdCol : uint8_t {
    kCOL1 = 1,
    kCOL2,
    kCOL3,
    kCOL4,
    kCOL5,
    kCOL6,
    kCOL7,
    kCOL8,
    kCOL9,
    kCOL10,
    kCOL11,
    kCOL12,
    kCOL13,
    kCOL14,
    kCOL15,
    kCOL16,
};
struct LCD_Config {
    LcdMode mode;
    Array<Pin, 8> dataPins;
    Port controlPort;
    Pin RSpin;
    Pin RWpin;
    Pin ENpin;
    LcdNibbles fourBitDataPin;
};
namespace stm32 {
namespace dev {
namespace hal {
namespace lcd {
class LCD {
 public:
    void Init(const LCD_Config &config);
    void ClearScreen(const LCD_Config &config);
    void SendChar(const LCD_Config &config, uint8_t character);
    void SendString(const LCD_Config &config, const std::string &str);
    void SendNum(const LCD_Config &config, int num);
    void SendFloat(const LCD_Config &config, double num);
    void SetPosition(const LCD_Config &config, LcdRows rowNum, LcdCol colNum);
    void EnableCursor(const LCD_Config &config);
    void DisableCursor(const LCD_Config &config);
    void ShiftLeft(const LCD_Config &config);
    void ShiftRight(const LCD_Config &config);
    void DisplayOn(const LCD_Config &config);
    void DisplayOff(const LCD_Config &config);
    void BlinkOn(const LCD_Config &config);
    void BlinkOff(const LCD_Config &config);
 private:
    void SendFallingEdgePulse(const LCD_Config &config);
    void SendCommand(const LCD_Config &config, LCDCommand command);
    void SendData(const LCD_Config &config, uint8_t data);
};
}   //  namespace lcd
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_LCD_H_

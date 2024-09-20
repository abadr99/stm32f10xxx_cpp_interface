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
#ifndef DEV_INC_HAL_LCD_H_
#define DEV_INC_HAL_LCD_H_

#include <string>

namespace stm32 {
namespace dev {
namespace hal {
namespace lcd {

enum LCDCommand : uint8_t {
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
    kEightBit = 8,
    kFourBit  = 4,
};


template<LcdMode M>
struct LCD_Config {
    using Pin  = stm32::dev::mcal::pin::Pin;
    using Port = stm32::dev::mcal::pin::Port;
    stm32::util::Array<Pin, M> dataPins;
    Port controlPort;
    Pin RSpin;
    Pin RWpin;
    Pin ENpin;
};

template<LcdMode M>
class Lcd {
 public:
    using Rows_t = uint8_t;
    using cols_t = uint8_t;
    explicit Lcd(const LCD_Config<M> &config_);
    void ClearScreen();
    void Print(char character);
    void Print(const std::string &str);
    void Print(int32_t num);
    void Print(double num);
    void SetPosition(Rows_t rowNum, cols_t colNum);
    void EnableCursor();
    void DisableCursor();
    void ShiftLeft();
    void ShiftRight();
    void DisplayOn();
    void DisplayOff();
    void BlinkOn();
    void BlinkOff();

 private:
    void Init();
    void SendFallingEdgePulse();
    void SendCommand(uint32_t command);
    void SendData(uint8_t data);
    void WriteOutputPins(uint8_t value);
    LCD_Config<M> config_;
};
}   //  namespace lcd
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_INC_HAL_LCD_H_

/**
 * @file Keypad.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_KEYPAD_H_
#define DEV_HAL_INC_KEYPAD_H_
using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
namespace stm32 {
namespace dev {
namespace hal {
namespace keypad {

class Keypad {
 public:
      Keypad(uint8_t numRows, uint8_t numCols);
      ~Keypad();
      void SetRowArr(Pin* rows);
      void setColArr(Pin* cols);
      void KeypadInit();
      uint8_t GetPressed(uint8_t** keypadButtons);
 private:
      uint8_t rowsNum;
      uint8_t colNum;
      Pin* KeypadRow;
      Pin* KeypadCol;
};
}  // namespace keypad
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  //  DEV_HAL_INC_KEYPAD_H_
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
#ifndef DEV_INC_HAL_KEYPAD_H_
#define DEV_INC_HAL_KEYPAD_H_
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
      void SetRowArr(const Pin* rows);
      void setColArr(const Pin* cols);
      void Init();
      uint8_t GetPressed(const uint8_t* const* keypadButtons);
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
#endif  //  DEV_INC_HAL_KEYPAD_H_

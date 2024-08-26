/**
 * @file DAC.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_DAC_H_
#define DEV_HAL_INC_DAC_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::utils::types;
using namespace stm32::dev::mcal::systick;
using namespace stm32::utils::array;
namespace stm32 {
namespace dev {
namespace hal {
namespace dac {

class Dac {
 public:
    Dac(Array<Pin, 8> dacPins, CLKSource clock);
    void DAC_Play(const Array<Pin, 8>& dacPins, uint32_t* songRaw, uint32_t songLength);
 private: 
    Array<Pin, 8> dacPins_;
    CLKSource clock_;
};
}   // namespace dac
}   // namespace hal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_HAL_INC_DAC_H_

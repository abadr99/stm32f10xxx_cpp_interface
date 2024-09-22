/**
 * @file LM32.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_LM35_H_
#define DEV_INC_HAL_LM35_H_
namespace stm32 {
namespace dev {
namespace hal {
namespace lm35 {
/**
 * @note: Config ADC before using LM35
 */
class LM35 {
 public:
    using adc_t = stm32::dev::mcal::adc::ADC;
    explicit LM35(const adc_t& adc);
    uint16_t GetTempVal();

 private:
    adc_t adc_;
};
}   //  namespace lm35
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //   DEV_INC_HAL_LM35_H_

/**
 * @file LM32.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_LM35_H_
#define DEV_HAL_INC_LM35_H_
namespace stm32 {
namespace dev {
namespace mcal { namespace adc {enum AdcPeripheral;}}
namespace hal {
namespace lm35 {
/**
 * @note: Config ADC before using LM35
 */
template<stm32::dev::mcal::adc::AdcPeripheral P>
class LM35 {
 public:
    using adc_t = stm32::dev::mcal::adc::ADC<P>;

    explicit LM35(const adc_t& adc);
    void Init();
    uint16_t GetTempVal();

 private:
    adc_t adc_;
};
}   //  namespace lm35
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //   DEV_HAL_INC_LM35_H_

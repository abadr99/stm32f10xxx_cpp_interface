/**
 * @file LDR.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_LDR_H_
#define DEV_HAL_INC_LDR_H_
namespace stm32 {
namespace dev {
namespace hal {
namespace ldr {
/**
 * @note: Config ADC before using LM35
 */
class LDR {
 public:
    using adc_t = stm32::dev::mcal::adc::ADC;

    explicit LDR(const adc_t& adc);
    void Init();
    uint16_t GetValue();

 private:
    adc_t adc_;
};
}   //  namespace ldr
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //   DEV_HAL_INC_LDR_H_

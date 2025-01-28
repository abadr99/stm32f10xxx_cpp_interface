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
#ifndef DEV_INC_HAL_LDR_H_
#define DEV_INC_HAL_LDR_H_
namespace stm32 {
namespace dev {
namespace hal {
namespace ldr {
/**
 * @brief Class to interface with an LDR sensor using an ADC.
 * 
 * @note Ensure that the ADC is properly configured before using this class.
 */
class LDR {
 public:
    /**
     * @brief Alias for the ADC type used with the LDR.
     */
    using adc_t = stm32::dev::mcal::adc::ADC;

    /**
     * @brief Constructs an LDR object with the specified ADC instance.
     * 
     * @param adc The ADC instance used for reading the LDR value.
     */
    explicit LDR(const adc_t& adc);

    /**
     * @brief Gets the current value from the LDR sensor.
     * 
     * This function reads the analog value from the ADC and returns it as
     * a 16-bit unsigned integer, representing the light intensity measured
     * by the LDR.
     * 
     * @return uint16_t The LDR sensor value.
     */
    uint16_t GetValue();

 private:
    adc_t adc_;   /**< ADC instance used for reading LDR sensor data. */
};
}   //  namespace ldr
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //   DEV_INC_HAL_LDR_H_

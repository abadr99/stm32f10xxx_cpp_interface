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
 * @brief Class for interfacing with an LM35 temperature sensor.
 * 
 * This class allows reading the temperature value from the LM35 sensor using an ADC.
 * 
 * @note The ADC must be configured before using this class.
 */
class LM35 {
 public:
    using adc_t = stm32::dev::mcal::adc::ADC;

    /**
     * @brief Constructs an LM35 sensor object.
     * 
     * @param adc The ADC peripheral instance used for reading the sensor value.
     */
    explicit LM35(const adc_t& adc);

    /**
     * @brief Retrieves the current temperature value from the LM35 sensor.
     * 
     * @return The raw temperature value (in ADC units).
     */
    uint16_t GetTempVal();

 private:
    adc_t adc_;   /**< The ADC instance used for sensor readings. */
};
}   //  namespace lm35
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //   DEV_INC_HAL_LM35_H_

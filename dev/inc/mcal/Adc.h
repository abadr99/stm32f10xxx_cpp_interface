/**
 * @file Adc.h
 * @brief 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_ADC_H_
#define DEV_INC_MCAL_ADC_H_
#include "mcal/stm32f103xx.h"
#define ADC_TIMEOUT (400)
using namespace stm32::registers::adc;
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace adc   {
/**
 * @brief Enumeration for ADC channels.
 */
enum AdcChannel {
    kChannel0,          /**< ADC Channel 0 */
    kChannel1,          /**< ADC Channel 1 */
    kChannel2,          /**< ADC Channel 2 */
    kChannel3,          /**< ADC Channel 3 */
    kChannel4,          /**< ADC Channel 4 */
    kChannel5,          /**< ADC Channel 5 */
    kChannel6,          /**< ADC Channel 6 */
    kChannel7,          /**< ADC Channel 7 */
    kChannel8,          /**< ADC Channel 8 */
    kChannel9,          /**< ADC Channel 9 */
    kChannel10,         /**< ADC Channel 10 */
    kChannel11,         /**< ADC Channel 11 */
    kChannel12,         /**< ADC Channel 12 */
    kChannel13,         /**< ADC Channel 13 */
    kChannel14,         /**< ADC Channel 14 */
    kChannel15,         /**< ADC Channel 15 */
    kChannel16,         /**< ADC Channel 16 */
    kChannel17          /**< ADC Channel 17 */
};

/**
 * @brief Enumeration for ADC data alignment.
 */
enum Alignment {
    kRight,     /**< Right-aligned data. */
    kLeft       /**< Left-aligned data. */
};

/**
 * @brief Enumeration for ADC modes.
 */
enum AdcMode {
    kSingleRegular = 0,         /**< Single regular conversion mode. */
    kContinous = 1,             /**< Continuous conversion mode. */
    kSingleInjected             /**< Single injected conversion mode. */
};

/**
 * @brief Enumeration for external trigger sources for ADC conversions.
 */
enum TriggerSource {
    kTimer1_CC1   = 0b000,      /**< Timer 1, channel 1. */
    kTimer1_CC2   = 0b001,      /**< Timer 1, channel 2. */
    kTimer1_CC3   = 0b010,      /**< Timer 1, channel 3. */
    kTimer2_CC2   = 0b011,      /**< Timer 2, channel 2. */
    kTimer3_TRGO  = 0b100,      /**< Timer 3 trigger output. */
    kEXTI_LINE11  = 0b110,      /**< External interrupt line 11. */
    kSoftware     = 0b111       /**< Software trigger. */
};

/**
 * @brief Enumeration for ADC sample times.
 */
enum SampleTime {
    kCycles_1_5,        /**< 1.5 ADC clock cycles. */
    kCycles_7_5,        /**< 7.5 ADC clock cycles. */
    kCycles_13_5,       /**< 13.5 ADC clock cycles. */
    kCycles_28_5,       /**< 28.5 ADC clock cycles. */
    kCycles_41_5,       /**< 41.5 ADC clock cycles. */
    kCycles_55_5,       /**< 55.5 ADC clock cycles. */
    kCycles_71_5,       /**< 71.5 ADC clock cycles. */
    kCycles_239_5       /**< 239.5 ADC clock cycles. */
};

/**
 * @brief Enumeration for ADC numbers.
 */
enum AdcNum {
    kADC1,      /**< ADC1 instance. */
    kADC2       /**< ADC2 instance. */
};

/**
 * @brief Structure to hold ADC configuration.
 */
struct AdcConfig {
    AdcNum number;              /**< ADC number (ADC1 or ADC2). */
    Alignment alignment;        /**< Data alignment. */
    AdcChannel channel;         /**< ADC channel. */
    AdcMode mode;               /**< ADC conversion mode. */
    TriggerSource trigSource;   /**< Trigger source for ADC conversions. */
    SampleTime sampleTime;      /**< ADC sample time. */
    // TODO(@noran): Add scan mode, multimode, and discontinuous mode.
};

/**
 * @brief Class for controlling the ADC.
 */
class ADC {
 public:
    /**
     * @brief Constructs an ADC object with the specified configuration.
     * 
     * @param config The configuration settings for the ADC.
     */
    explicit ADC(const AdcConfig& config);

    /**
     * @brief Initializes the ADC.
     */
    void Init();

    /**
     * @brief Starts a single regular conversion.
     * 
     * @return The result of the conversion.
     */
    uint16_t StartSingleConversion();

    /**
     * @brief Starts continuous conversions.
     */
    void StartContinuousConversion();

    /**
     * @brief Reads the result of a continuous conversion.
     * 
     * @return The result of the conversion.
     */
    uint16_t ReadContinuousConversion();

    /**
     * @brief Stops continuous conversions.
     */
    void StopContinuousConversion();

    /**
     * @brief Starts an injected conversion.
     * 
     * @return The result of the injected conversion.
     */
    uint16_t StartInjectedConversion();

    /**
     * @brief Enables the ADC interrupt.
     */
    void EnableInterrupt();

    /**
     * @brief Disables the ADC interrupt.
     */
    void DisableInterrupt();

    /**
     * @brief Disables the ADC.
     */
    void Disable();

    /**
     * @brief Gets the ADC number (ADC1 or ADC2).
     * 
     * @return The ADC number.
     */
    AdcNum GetAdcNum();

 private:
    const AdcConfig& config_;        /**< ADC configuration settings. */
    volatile ADCRegDef* ADC_reg;    /**< Pointer to the ADC register definition. */

    /**
     * @brief Configures the sample time for the selected ADC channel.
     */
    void ConfigureChannelSample();
};
}   // namespace adc
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_INC_MCAL_ADC_H_ 

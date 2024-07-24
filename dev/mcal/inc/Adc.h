/**
 * @file Adc.h
 * @brief 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_ADC_H_
#define DEV_MCAL_INC_ADC_H_
#include "../../mcal/inc/stm32f103xx.h"
using namespace stm32::registers::adc;
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace adc   {
enum  Channel {
        Channel0,
        Channel1,
        Channel2,
        Channel3,
        Channel4,
        Channel5,
        Channel6,
        Channel7,
        Channel8,
        Channel9,
        Channel10,
        Channel11,
        Channel12,
        Channel13,
        Channel14,
        Channel15,
        Channel16,
        Channel17
};
enum  Alignment {
        RIGHT = 0,
        LEFT = 1
};
enum Prescaler {
        DIV2 = 0,
        DIV4,
        DIV6,
        DIV8
};
enum Mode {
        SINGLE = 0,
        CONTINUOUS = 1
};
struct ADCConfig {
Alignment alignment = RIGHT;
Prescaler prescaler = DIV2;
Channel channel;
//  bool useDMA; TODO
// bool scanMode; TODO
};
enum  AdcPeripheral {
    kADC1,
    kADC2
};
template<AdcPeripheral  ADC_NUM>
class ADC {
 public:
explicit ADC(const ADCConfig& config);
void init();
uint16_t startSingleConversion();
void startContinuousConversion();
uint16_t readContinuousConversion();
void stopContinuousConversion();
 private:
ADCConfig& config_;
volatile ADCRegDef* ADC_reg;
};
}   // namespace adc
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_ADC_H_ 

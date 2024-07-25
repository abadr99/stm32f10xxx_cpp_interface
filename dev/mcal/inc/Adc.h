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
enum Mode {
        SINGLE = 0,
        CONTINUOUS = 1,
        INJECTED
};
enum TriggerSource {
        TIMER1_CC1 = 0b000,
        TIMER1_CC2 = 0b001,
        TIMER1_CC3 = 0b010,
        TIMER2_CC2 = 0b011,   
        TIMER3_TRGO = 0b100,
        EXTI_LINE11 = 0b110,  
        SOFTWARE = 0b111
};
enum  SampleTime {
        CYCLES_1_5,
        CYCLES_7_5,
        CYCLES_13_5,
        CYCLES_28_5,
        CYCLES_41_5,
        CYCLES_55_5,
        CYCLES_71_5,
        CYCLES_239_5
};
struct ADCConfig {
Alignment alignment = RIGHT;
Channel channel;
Mode mode = SINGLE;
TriggerSource trigSource = SOFTWARE;
SampleTime sampleTime = CYCLES_55_5;
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
uint16_t  startInjectedConversion();
void EnableInterrupt();
void DisableInterrupt();
void Disable();
 private:
ADCConfig& config_;
volatile ADCRegDef* ADC_reg;
void configureChannelSample();
};
}   // namespace adc
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_ADC_H_ 

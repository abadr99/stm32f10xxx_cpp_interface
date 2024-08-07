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
#define ADC_TIMEOUT (400)
using namespace stm32::registers::adc;
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace adc   {
enum  Channel {
        kChannel0,
        kChannel1,
        kChannel2,
        kChannel3,
        kChannel4,
        kChannel5,
        kChannel6,
        kChannel7,
        kChannel8,
        kChannel9,
        kChannel10,
        kChannel11,
        kChannel12,
        kChannel13,
        kChannel14,
        kChannel15,
        kChannel16,
        kChannel17
};
enum  Alignment {
        kRIGHT,
        kLEFT
};
enum Mode {
        kSINGLE = 0,
        kCONTINUOUS = 1,
        kINJECTED
};
enum TriggerSource {
        kTIMER1_CC1 = 0b000,
        kTIMER1_CC2 = 0b001,
        kTIMER1_CC3 = 0b010,
        kTIMER2_CC2 = 0b011,   
        kTIMER3_TRGO = 0b100,
        kEXTI_LINE11 = 0b110,  
        kSOFTWARE = 0b111
};
enum  SampleTime {
        kCYCLES_1_5,
        kCYCLES_7_5,
        kCYCLES_13_5,
        kCYCLES_28_5,
        kCYCLES_41_5,
        kCYCLES_55_5,
        kCYCLES_71_5,
        kCYCLES_239_5
};
struct ADCConfig {
       Alignment alignment;
       Channel channel;
       Mode mode;
       TriggerSource trigSource;
       SampleTime sampleTime;
       // TODO(@noran97): scan mode , multimode and discontinous mode
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

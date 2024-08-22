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
enum  AdcChannel {
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
        kRight,
        kLeft
};
enum AdcMode {
        kSingle = 0,
        kContinous = 1,
        kInjected
};
enum TriggerSource {
        kTimer1_CC1 = 0b000,
        kTimer1_CC2 = 0b001,
        kTimer1_CC3 = 0b010,
        kTimer2_CC2 = 0b011,   
        kTimer3_TRGO = 0b100,
        kEXTI_LINE11 = 0b110,  
        kSoftware = 0b111
};
enum  SampleTime {
        kCycles_1_5,
        kCycles_7_5,
        kCycles_13_5,
        kCycles_28_5,
        kCycles_41_5,
        kCycles_55_5,
        kCycles_71_5,
        kCycles_239_5
};
enum  AdcNum {
    kADC1,
    kADC2
};
struct AdcConfig {
       AdcNum number;
       Alignment alignment;
       AdcChannel channel;
       AdcMode mode;
       TriggerSource trigSource;
       SampleTime sampleTime;
       // TODO(@noran97): scan mode , multimode and discontinous mode
};

class ADC {
 public:
     explicit ADC(const AdcConfig& config);
     void Init();
     uint16_t StartSingleConversion();
     void StartContinuousConversion();
     uint16_t ReadContinuousConversion();
     void StopContinuousConversion();
     uint16_t  StartInjectedConversion();
     void EnableInterrupt();
     void DisableInterrupt();
     void Disable();
 private:
     const AdcConfig& config_;
     volatile ADCRegDef* ADC_reg;
     void ConfigureChannelSample();
};
}   // namespace adc
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_ADC_H_ 

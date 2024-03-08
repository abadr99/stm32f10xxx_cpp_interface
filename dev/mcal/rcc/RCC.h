#ifndef DEV_MCAL_RCC_H
#define DEV_MCAL_RCC_H

namespace stm32{
namespace dev{
namespace mcal{
namespace rcc{


enum ClkConfig_t
{


};

enum AHBPrescaler_t
{
    AHP_not_divided        = 0b0000,
    AHP_CLK_DIVIDED_BY_2   = 0b1000,
    AHP_CLK_DIVIDED_BY_4   = 0b1001,
    AHP_CLK_DIVIDED_BY_8   = 0b1010,
    AHP_CLK_DIVIDED_BY_16  = 0b1011,
    AHP_CLK_DIVIDED_BY_64  = 0b1100,
    AHP_CLK_DIVIDED_BY_128 = 0b1101,
    AHP_CLK_DIVIDED_BY_256 = 0b1110,
    AHP_CLK_DIVIDED_BY_512 = 0b1111
};

enum APBPrescaler_t
{
    APB_NOT_DIVIDED       = 0b000, 
    APB_CLK_DIVIDED_BY_2  = 0b100,  
    APB_CLK_DIVIDED_BY_4  = 0b101,  
    APB_CLK_DIVIDED_BY_8  = 0b110,  
    APB_CLK_DIVIDED_BY_16 = 0b111

};

enum MCOModes_t
{
	SystemClock,
	HSI_CLOCK,
	HSE_CLOCK,
	PLL_CLOCK
};

class RCC
{
public:
    static void InitSysClock(ClkConfig_t systemClk);
    static void SetAHBPrescaler(AHBPrescaler_t prescaler);
    static void SetAPB1Prescaler(APBPrescaler_t prescaler);
    static void SetAPB2Prescaler(APBPrescaler_t prescaler);
    static void SetMCOPinClk(MCOModes_t mode);
};

} //namespace stm32
} //namespace dev  
} //namespace mcal
} //namespace rcc




#endif /* DEV_MCAL_RCC_H */
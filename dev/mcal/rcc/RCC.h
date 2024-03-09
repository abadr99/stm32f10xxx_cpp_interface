/**
 * @file RCC.h
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-03-8
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_MCAL_RCC_H_
#define DEV_MCAL_RCC_H_

namespace stm32{
namespace dev{
namespace mcal{
namespace rcc{

enum ClkConfig_t
{
    HSI = 0b00,
    HSE_DIV = 0b10,

    PLL_HSI_MUL_2  = 0b000001,
    PLL_HSI_MUL_3  = 0b000101,
    PLL_HSI_MUL_4  = 0b001001,
    PLL_HSI_MUL_5  = 0b001101,
    PLL_HSI_MUL_6  = 0b010001,
    PLL_HSI_MUL_7  = 0b010101,
    PLL_HSI_MUL_8  = 0b011001,
    PLL_HSI_MUL_9  = 0b011101,
    PLL_HSI_MUL_10 = 0b100001,
    PLL_HSI_MUL_11 = 0b100101,
    PLL_HSI_MUL_12 = 0b101001,
    PLL_HSI_MUL_13 = 0b101101,
    PLL_HSI_MUL_14 = 0b110001,
    PLL_HSI_MUL_15 = 0b110101,
    PLL_HSI_MUL_16 = 0b111001,

    PLL_HSE_DIV_1_MUL_2  = 0b0000011,
    PLL_HSE_DIV_1_MUL_3  = 0b0001011,
    PLL_HSE_DIV_1_MUL_4  = 0b0010011,
    PLL_HSE_DIV_1_MUL_5  = 0b0011011,
    PLL_HSE_DIV_1_MUL_6  = 0b0100011,
    PLL_HSE_DIV_1_MUL_7  = 0b0101011,
    PLL_HSE_DIV_1_MUL_8  = 0b0110011,
    PLL_HSE_DIV_1_MUL_9  = 0b0111011,
    PLL_HSE_DIV_1_MUL_10 = 0b1000011,
    PLL_HSE_DIV_1_MUL_11 = 0b1001011,
    PLL_HSE_DIV_1_MUL_12 = 0b1010011,
    PLL_HSE_DIV_1_MUL_13 = 0b1011011,
    PLL_HSE_DIV_1_MUL_14 = 0b1100011,
    PLL_HSE_DIV_1_MUL_15 = 0b1101011,
    PLL_HSE_DIV_1_MUL_16 = 0b1110011,

    PLL_HSE_DIV_2_MUL_2  = 0b0000111,
    PLL_HSE_DIV_2_MUL_3  = 0b0001111,
    PLL_HSE_DIV_2_MUL_4  = 0b0010111,
    PLL_HSE_DIV_2_MUL_5  = 0b0011111,
    PLL_HSE_DIV_2_MUL_6  = 0b0100111,
    PLL_HSE_DIV_2_MUL_7  = 0b0101111,
    PLL_HSE_DIV_2_MUL_8  = 0b0110111,
    PLL_HSE_DIV_2_MUL_9  = 0b0111111,
    PLL_HSE_DIV_2_MUL_10 = 0b1000111,
    PLL_HSE_DIV_2_MUL_11 = 0b1001111,
    PLL_HSE_DIV_2_MUL_12 = 0b1010111,
    PLL_HSE_DIV_2_MUL_13 = 0b1011111,
    PLL_HSE_DIV_2_MUL_14 = 0b1100111,
    PLL_HSE_DIV_2_MUL_15 = 0b1101111,
    PLL_HSE_DIV_2_MUL_16 = 0b1110111
};

enum AHBPrescaler_t
{
    AHP_NOT_DIVIDED        = 0b0000,
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

}//namespace stm32
}//namespace dev
}//namespace mcal
}//namespace rcc

#endif /* DEV_MCAL_RCC_H */

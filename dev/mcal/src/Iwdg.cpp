/**
 * @file Iwdg.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Iwdg.h"

using namespace stm32::dev::mcal::iwdg; // NOLINT[build/namespaces]
using namespace stm32::registers::iwdg; 

template<Prescaler prescaler, uint16_t reloadVal>
Iwdg<prescaler, reloadVal>::Iwdg() {
    IWDG->KR = 0x5555;
    while (IWDG->SR.PVU == 1) {}
    IWDG->PR = prescaler;
    while (IWDG->SR.RVU == 1) {}
    IWDG->RLD = reloadVal;
    IWDG->KR = 0xCCCC;
}
template<Prescaler prescaler, uint16_t reloadVal>
void Iwdg<prescaler, reloadVal>::Refresh() {
    IWDG->KR = 0xAAAA;
}

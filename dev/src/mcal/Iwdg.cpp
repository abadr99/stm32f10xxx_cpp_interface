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
#include "stm32f103xx.h"
#include "BitSet.h"
#include "Assert.h"
#include "BitManipulation.h"
#include "Util.h"
#include "Iwdg.h"

using namespace stm32::dev::mcal::iwdg; // NOLINT[build/namespaces]
using namespace stm32::registers::iwdg; 

Iwdg::Iwdg(Prescaler prescaler, uint16_t reloadVal) {
    IWDG->KR = 0x5555;
    util::BusyWait([&](){return IWDG->SR.PVU;});
    IWDG->PR = prescaler;
    util::BusyWait([&](){return IWDG->SR.RVU;});
    IWDG->RLD = reloadVal;
    IWDG->KR = 0xCCCC;
}
void Iwdg::Refresh() {
    IWDG->KR = 0xAAAA;
}

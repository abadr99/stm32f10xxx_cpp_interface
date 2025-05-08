/**
 * @file main.cpp
 * @author Noura Gamal
 * @brief 
 * @version 0.1
 * @date 2025-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// commit-id: 7f24e1cbbb8304f6f43bdb2fb672275bd66bfc17
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Systick.h"
#include "mcal/Flash.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::mcal::flash;


int main() {
    Flash flash;
    flash.Init();
    FlashTypeDef ctx{};
    ctx.lockState = LockState::kUnLocked;
    ctx.errorcode = FlashError::kNone;
    constexpr uint32_t kTestAddress = 0x0800FC00;
    constexpr uint16_t kTestData    = 0xABCD;
    flash.Unlock();
    flash.PageErase(kTestAddress);
    Status result = flash.Program(&ctx, TypeProgram::kHalfWord, kTestAddress, kTestData);
    if (result == Status::kOK) {
        //  Programming successful
    } else {
        FlashError error = flash.GetError(ctx);
    }
    flash.Lock();
    while (1) { }
}

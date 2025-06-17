/**
 * @file main.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2025-03-4
 * @copyright Copyright (c) 2024
 */

#include "mcal/stm32f103xx.h"
 #include "utils/Types.h"
 #include "utils/BitManipulation.h"
 #include "mcal/Pin.h"
 #include "mcal/Gpio.h"
 #include "mcal/Rcc.h"
 #include "mcal/Timer.h"
 #include "mcal/Systick.h"
 #include "mcal/Usart.h"
 #include "mcal/Exti.h"
 #include "mcal/Nvic.h"
 #include "hal/HC05.h"
 #include "hal/DC_Motor.h"
 #include "hal/Buzzer.h"
 #include "hal/IR.h"
 #include "hal/Car_Control.h"
 #include "hal/LKA.h"
 
using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::timer;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::mcal::usart;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::exti;
using namespace stm32::dev::hal::bluetooth;
using namespace stm32::dev::hal::dc_motor;
using namespace stm32::dev::hal::buzzer;
using namespace stm32::dev::hal::ir;
using namespace stm32::dev::app::car_control;
using namespace stm32::dev::app::lka;

void RCC_CONFIG();
void GPIO_CONFIG();
void SYSTICK_CONFIG();
int main(void) {
    RCC_CONFIG();
    GPIO_CONFIG();
    SYSTICK_CONFIG();
    Exti::Init();
    Nvic::Init();
    Pin right1_B12(kPortB, kPin12, PinMode::kOutputPushPull_10MHz);
    Pin left1_B13(kPortB, kPin13, PinMode::kOutputPushPull_10MHz);
    Pin right2_B14(kPortB, kPin14, PinMode::kOutputPushPull_10MHz);
    Pin left2_B15(kPortB, kPin15, PinMode::kOutputPushPull_10MHz);
    
    DC_Motor dc_motor1(right1_B12 , left1_B13);
    DC_Motor dc_motor2(right2_B14 , left2_B15);

    TimerConfig config = {
            .Timerid = kTimer2,
            .Direction = kUP,
            .Prescaler = 72,
            .interrupt = kDisable
            };
    Timer tim2(config);

    TimerOCTypeDef oc = {
        .mode = kPWM1,
        .state = kEnable,
        .polarity = kActiveHigh,
        .period = 100
    };
    tim2.OCMode(oc);
  /*Speed of motoors*/
    tim2.SetCompare1(oc, kChannel1, 100);
  /*******************************USART********************************/
  UsartConfig usart1_cfg = {.number = kUsart1,
                            .mode = kRx,
                            .numOfSB = kSb_1_,
                            .dataBits = kDataBits_8_,
                            .parityMode = kNo_Parity,
                            .flowControlState = kNone,
                            .baudRate = 9600};
  Usart usart1(usart1_cfg);
  /************************************HC-05************************* */
  HC05 bluetooth(usart1);
  /**********************************Car************************** */
  Car_Control car(dc_motor1, dc_motor2, bluetooth);
  while (1) {
     /*bluetooth*/
     car.ProcessCommand();
    tim2.SetCompare1(oc, kChannel1, 100);
    }
}
void RCC_CONFIG() {
    Rcc::Init(); 
    Rcc::InitSysClock(kHse, kClock_1x);
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPA);
    Rcc::Enable(Peripheral::kIOPB);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kTIM2);
    Rcc::Enable(Peripheral::kCAN);
    Rcc::InitSysClock();
}
void GPIO_CONFIG() {
    Gpio::Init();
    Pin PWM_A0(kPortA, kPin0, PinMode::kAlternativePushPull_50MHz);
    Gpio::Set(PWM_A0);
}
void SYSTICK_CONFIG() {
    Systick::Init();
    Systick::Enable(kAHB_Div_8);
}
/***Pins 
B12-->A motor1
B13-->B motor1
B14-->A motor2
B15-->B motor2
A0-->PWM
A1-->IR1
A2-->IR2
A10-->Tx for bluetooth
*/

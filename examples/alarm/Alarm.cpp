#include "utils/Types.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "hal/Led.h"
#include "hal/Buzzer.h"
#include "Alarm.hpp"

using namespace stm32::type;
using namespace stm32::dev::mcal;
using namespace stm32::dev::mcal::pin;

Alarm::Alarm() 
: led_(Pin(kPortA, kPin0, PinMode::kAlternativeOpenDrain_10MHz))
, buz_(Pin(kPortA, kPin1, PinMode::kAlternativeOpenDrain_10MHz))
{
    /* EMPTY */
}

void Alarm::Run(bool v) {
    if (v) {
        led_.TurnOn();
        buz_.TurnOn();
        return;
    }
    led_.TurnOff();
    buz_.TurnOff();
} 
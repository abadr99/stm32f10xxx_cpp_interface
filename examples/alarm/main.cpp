#include <stdint.h>
#include <cstdlib>
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "Alarm.hpp"

int main() {
    
    Alarm a;
    while(1) {
        std::srand(1);
        // random value that will determine if the system 
        // should work or not (between 10 and 20)
        uint32_t val = 10 + std::rand() % (20 - 10 + 1);
        // Alarm will work if the value is smaller than 15
        a.Run(val < 15);
    }
}
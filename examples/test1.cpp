/**
 * @file test1.cpp
 * @brief Example program demonstrating usage of the LED class with libgpiod.
 *
 * This program initializes an LED connected to GPIO27 on /dev/gpiochip0 and 
 * makes it blink using the predefined warning pattern.
 *
 * ### Build:
 * @code
 * mkdir -p ./bin && g++ -o ./bin/test1 test1.cpp ../LED.cpp -lpthread -lgpiod
 * @endcode
 *
 * ### Run (requires root privileges):
 * @code
 * sudo ./bin/test1
 * @endcode
 */

// ###########################################################
// Include libraries:
#include <iostream>
#include "../LED.h"
#include <gpiod.h>

// ############################################################

/**
 * @brief Default GPIO chip device file.
 */
static constexpr const char* chipAddress = "/dev/gpiochip0";

/**
 * @brief GPIO line offset number for the LED (GPIO27).
 */
const unsigned int line_offset = 27;  

// ############################################################

/**
 * @brief Program entry point.
 *
 * This function demonstrates how to:
 * - Create an LED object
 * - Initialize it with begin()
 * - Blink it with the warning pattern
 *
 * @return 0 if the program executes successfully,  
 *         1 if an error occurs during LED initialization.
 */
int main()
{
    LED led(chipAddress, line_offset, 1);

    if (led.begin() == false)
    {
        std::cout << led.errorMessage << std::endl;
        return 1;
    }

    led.blinkWarning_1();

    return 0;
}

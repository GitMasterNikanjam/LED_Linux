// ############################################################################
// Include libraries:

#include "LED.h"
#include <thread>
#include <chrono>

// ############################################################################
// LED class:

LED::LED(const char* chipAddress, unsigned int line_offset, uint8_t mode)
{
    _mode = mode;
    _line_offset = line_offset;
    _chipAddress = chipAddress;
    _consumer = "LED";

    if(_mode == 0)
    {
        _on = 0;

    }
    else
    {
        _on = 1;
    }
}

bool LED::begin(void)
{
    _chip = gpiod_chip_open(_chipAddress);
    if (!_chip) 
    {
        errorMessage =  "Failed to open chip.";
        return false;
    }

    _line = gpiod_chip_get_line(_chip, _line_offset);
    if (!_line) 
    {
        errorMessage = "Failed to get line at offset " + std::to_string(_line_offset);
        return false;
    }

    if (gpiod_line_request_output(_line, _consumer, !_on) < 0) 
    {
        errorMessage = "Request line as output failed.";
        return false;
    }

    return true;
}

void LED::clean(void)
{
    if (_line) gpiod_line_release(_line);
}

void LED::blinkWarning_1(void)
{
    for(int i=1; i<=5; i++)
    {
        gpiod_line_set_value(_line, _on);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        gpiod_line_set_value(_line, !_on);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void LED::blinkInit(void)
{
    gpiod_line_set_value(_line, _on);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    gpiod_line_set_value(_line, !_on);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void LED::blinkExit(void)
{
    for(int i=1; i<=2; i++)
    {
        gpiod_line_set_value(_line, _on);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        gpiod_line_set_value(_line, !_on);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}




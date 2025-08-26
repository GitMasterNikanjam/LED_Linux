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
    _blinkCounter = 0;
    _blinkFlag = false;
    _blinkDelay = 0;
    _blinkNumber = 0;
    _initFlag = false;

    if(_mode == 0)
    {
        _on = 0;

    }
    else
    {
        _on = 1;
    }
}

LED::~LED()
{
    clean();
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

    _initFlag = true;

    return true;
}

void LED::clean(void)
{
    // Leave the pin as input (best-effort) before dropping our handle
    if (_line)
    {
        // 1) Drop whatever configuration we had (output, event, etc.)
        gpiod_line_release(_line);

        // 2) Best-effort: set it to input, then release again
        if (gpiod_line_request_input(_line, "AUX::clean(set-input)") == 0)
        {
            gpiod_line_release(_line);
        }
        else
        {
            // If this fails (e.g., another process grabbed it), we still proceed.
            // Optionally keep the last error so caller can inspect it.
            // Requires: #include <cerrno>, <cstring>
            errorMessage = "gpiod_line_request_input() failed while cleaning.";
            return;
        }

        _line = nullptr;
    }

    // Optional: clear only if you don't want to keep the error above.
    errorMessage.clear();

    _initFlag = false;
}

void LED::on(void)
{
    gpiod_line_set_value(_line, _on);
}

void LED::off(void)
{
    gpiod_line_set_value(_line, !_on);
}

void LED::toggle(void)
{
    int state = gpiod_line_get_value(_line);

    if(state < 0)
    {
        return;
    }
    else
    {
        gpiod_line_set_value(_line, !state);
    }
}

void LED::blink(uint16_t duration, uint8_t number, bool blockingMode)
{
    if(_initFlag == false)
    {
        return;
    }

    if( (duration == 0) || (number == 0) )
    {
        _T = 0;
        _blinkFlag = false;
        off();
    }

    _blinkDelay = (float)duration / (2.0 * number);

    if(blockingMode == true)
    {
        for(int i=1; i<=number; i++)
        {
            on();
            std::this_thread::sleep_for(std::chrono::milliseconds(_blinkDelay));
            off();
            std::this_thread::sleep_for(std::chrono::milliseconds(_blinkDelay));
        }
    }
    else
    {
        _blinkNumber = number;
        _T = timer.millis();
        _blinkCounter = 0;
        _blinkFlag = true;
        on();
    }
}

void LED::blinkUpdate(void)
{
    uint64_t time = timer.millis();

    if( (_blinkFlag == false) || (time <= _T) )
    {
        return;
    }
    
    if( (time - _T) >= _blinkDelay)
    {
        ++_blinkCounter;
        if(_blinkCounter >= (2* _blinkNumber) )
        {
            _blinkFlag = false;
            off();
            return;
        }
        toggle();
        _T = time;   
    }
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




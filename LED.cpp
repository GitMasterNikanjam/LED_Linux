#include "LED.h"

    LED::LED(uint8_t pin, uint8_t mode)
    {
        _pin = pin;
        _mode = mode;

        if(_mode == LOW)
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
        if(_pin > 30)
        {
            errorMessage = "Error LED object. pin configuration is in wrong range.";
            return false;
        }

        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(_pin, !_on);

        return true;
    }

    void LED::clean(void)
    {
        bcm2835_gpio_fsel(_pin, BCM2835_GPIO_FSEL_INPT);
        bcm2835_gpio_set_pud(_pin, BCM2835_GPIO_PUD_OFF);
    }

    void LED::blinkWarning_1(void)
    {
        for(int i=1; i<=5; i++)
        {
            bcm2835_gpio_write(_pin, _on);
            bcm2835_delay(100);
            bcm2835_gpio_write(_pin, !_on);
            bcm2835_delay(100);
        }
    }

    void LED::blinkInit(void)
    {
        bcm2835_gpio_write(_pin, _on);
        bcm2835_delay(100);
        bcm2835_gpio_write(_pin, !_on);
        bcm2835_delay(100);
    }

    void LED::blinkExit(void)
    {
        for(int i=1; i<=2; i++)
        {
            bcm2835_gpio_write(_pin, _on);
            bcm2835_delay(50);
            bcm2835_gpio_write(_pin, !_on);
            bcm2835_delay(100);
        }
    }
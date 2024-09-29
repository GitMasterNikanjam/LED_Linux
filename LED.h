#ifndef _LED_H_
#define _LED_H_

    #include <iostream>
    #include <bcm2835.h>

    // LED object.
    class LED
    {
        public:

            std::string errorMessage;

            /*
                LED object constructor. Set LED pin and its active low/high mode. Not apply setting.
                Hint: begin() method needs after this for apply setting on hardware.
                mode: active low/high mode. Actice low:0, Active high:1 
            */
            LED(uint8_t pin, uint8_t mode); 

            /*
                Apply setting on hardware. Start LED action.
                @return true if successed.
            */
            bool begin(void);

            /*
                Clean setting on hardware. Stop  LED action. 
            */
            void clean(void);

            /*
                blink for warning type 1.
                Hint: it excutes in blocking mode.
            */
            void blinkWarning_1(void);

            /*
                blink for initialization actions.
                Hint: it excutes in blocking mode.
            */
            void blinkInit(void);

            /*
                blink for exite/stop actions.
                Hint: it excutes in blocking mode.
            */
            void blinkExit(void);

        private:

            // GPIO pin number
            uint8_t _pin;
            
            // Active low/high mode. Actice low:0, Active high:1 
            uint8_t _mode;

            // Digital value for LED turn on state.
            uint8_t _on;

    };

#endif  // _LED_H_
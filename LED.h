// ##################################################################################
#pragma once

// Enable libgpiod v1 API on systems that have libgpiod v2
#ifndef GPIOD_USE_LEGACY
    #define GPIOD_USE_LEGACY
#endif

// ##################################################################################
// Include libraries:
#include <iostream>
#include <gpiod.h>
#include "../TimerControl_OS/TimerControl.h"

// ##################################################################################
/**
 * @class LED
 * @brief A simple LED control class using libgpiod.
 *
 * This class provides methods to control an LED connected to a GPIO line via
 * the libgpiod library. It allows initialization, cleanup, and predefined
 * blink patterns for various application states (warnings, initialization,
 * exit/stop).
 *
 * Typical usage:
 * @code
 * LED led("/dev/gpiochip0", 24, 1);   // Active-high LED on GPIO24
 * if (led.begin()) {
 *     led.blinkInit();
 *     // ...
 *     led.clean();
 * }
 * @endcode
 */
class LED
{
public:

    /**
     * @brief Holds an error message if operations fail.
     */
    std::string errorMessage;

    /**
     * @brief Construct a new LED object.
     *
     * This only sets up the LED pin and its active mode (low/high).
     * Hardware configuration is not applied until begin() is called.
     *
     * @param chipAddress Path to the GPIO chip device (e.g. "/dev/gpiochip0").
     * @param line_offset GPIO line offset number for the LED.
     * @param mode Active mode: 0 = active-low, 1 = active-high.
     *
     * @note Call begin() after construction to apply the settings on hardware.
     */
    LED(const char* chipAddress, unsigned int line_offset, uint8_t mode); 

    ~LED();
    
    /**
     * @brief Apply settings on the hardware and enable LED control.
     *
     * @return true if the hardware setup was successful, false otherwise.
     */
    bool begin(void);

    /// @brief Turn on the LED.
    void on(void);

    /// @brief Turn off the LED.
    void off(void);

    /// @brief Toggle the LED.
    void toggle(void);

    /**
     * @brief Clean up hardware resources and disable LED control.
     */
    void clean(void);

    /**
     * @brief Blink LED with the warning pattern (type 1).
     *
     * This method executes in blocking mode.
     */
    void blinkWarning_1(void);

    /**
     * @brief Blink LED to indicate initialization actions.
     *
     * This method executes in blocking mode.
     */
    void blinkInit(void);

    /**
     * @brief Blink LED to indicate exit/stop actions.
     *
     * This method executes in blocking mode.
     */
    void blinkExit(void);

    /**
     * @brief Blink the LED.
     * @param duration: is the total duration time for toggle LED. [ms]
     * @param number: is the number of toggling in certain duration time.
     * @param blockingMode: is the blink mode for blocking mode enable/disable. Default value is true that means blinking is in blocking mode.
     * @note - Total time duration for toggle operation is: (duration)
     */
    void blink(uint16_t duration, uint8_t number, bool blockingMode = true);

    /**
     * @brief Return blinking status for non blocking mode.
     * @return - true if blinking proccess is not finished.
     * @return - false if blinking proccess is finished.
     *  */ 
    bool isBlinking(void) {return _blinkFlag;};

    /**
     * @brief Update blinking status in non blocking mode.
     * @note - This method should be used in the main loop or in a periodic function.
     */
    void blinkUpdate(void);

private:
    
    gpiod_chip* _chip;           ///< Handle to the GPIO chip.
    const char* _chipAddress;    ///< Path to the GPIO chip device.
    gpiod_line* _line;           ///< Handle to the GPIO line.
    const char* _consumer;       ///< Consumer label for GPIO request.
    unsigned int _line_offset;   ///< GPIO line offset used by the LED.

    TimerControl timer;

    /// @brief The time update for led blinking in non blocking mode.
    uint32_t _T;

    /// @brief Counter for blink led in non blocking mode.
    uint8_t _blinkCounter;

    /// @brief The flag for blink led state in non blocking mode.
    bool _blinkFlag;

    /// @brief The delay of time for one blink led in non blocking mode. [ms]
    uint16_t _blinkDelay;

    /// @brief The number of blink led in non blocking mode.
    uint8_t _blinkNumber;

    /// @brief The flag for LED.init() is succeeded or not.
    bool _initFlag;

    /**
     * @brief Active mode for the LED.
     * - 0 = active-low
     * - 1 = active-high
     */
    uint8_t _mode;

    /**
     * @brief Digital value representing LED ON state depending on active mode.
     */
    uint8_t _on;
};

# LED_Linux

A lightweight C++ library to control LEDs on Linux systems using **[libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/)**.  
This library wraps GPIO line control into a simple `LED` class, providing initialization, cleanup, and predefined blink patterns for common application states.

---

## ✨ Features
- Simple object-oriented interface to control an LED
- Works with [libgpiod](https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/) (v1.x / v2.x)
- Support for **active-high** and **active-low** LEDs
- Predefined blink patterns:
  - `blinkWarning_1()` → warning indicator
  - `blinkInit()` → initialization indicator
  - `blinkExit()` → exit/stop indicator
- Easy integration into multi-threaded applications

---

## 📦 Dependencies
- **C++11 or later**
- **libgpiod** (install via package manager)

### Install libgpiod on Ubuntu/Debian
```bash
sudo apt update
sudo apt install libgpiod-dev gpiod
````

---

## 🔧 Build Instructions

Clone your project and compile with g++:

```bash
mkdir -p ./bin
g++ -o ./bin/test1 test1.cpp LED.cpp -lpthread -lgpiod
```

Run the program (may require root privileges depending on GPIO permissions):

```bash
sudo ./bin/test1
```

---

## 🚀 Usage Example

```cpp
#include "LED.h"

int main() {
    // Create LED object: gpiochip0, line 24, active-high mode
    LED led("/dev/gpiochip0", 24, 1);

    if (!led.begin()) {
        std::cout << "Error: " << led.errorMessage << std::endl;
        return 1;
    }

    // Blink initialization pattern
    led.blinkInit();

    // Blink warning pattern
    led.blinkWarning_1();

    // Clean up
    led.clean();

    return 0;
}
```

---

## 📚 API Overview

### Constructor

```cpp
LED(const char* chipAddress, unsigned int line_offset, uint8_t mode);
```

* `chipAddress`: Path to GPIO chip (e.g., `"/dev/gpiochip0"`)
* `line_offset`: Line offset number (GPIO pin index)
* `mode`: `0` = active-low, `1` = active-high

### Methods

* `bool begin()` → Apply settings and request line
* `void clean()` → Release GPIO line
* `void blinkWarning_1()` → Blink 5x (warning pattern)
* `void blinkInit()` → Short blink (initialization)
* `void blinkExit()` → Double blink (exit/stop)

---

## 🛠️ Project Structure

```
LED_Linux/
│── LED.h          # LED class declaration
│── LED.cpp        # LED class implementation
│── test1.cpp      # Example usage
│── README.md      # Documentation
```

---

## 📄 License

This project is licensed under the **MIT License**.
You are free to use, modify, and distribute it in your projects.

---

## 🙌 Contributing

Pull requests are welcome! If you find a bug or want to add new LED patterns, feel free to open an issue.

---


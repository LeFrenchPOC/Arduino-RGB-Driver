<h1 align="center">Welcome to RGB Driver 👋</h1>
<p>
  <a href="https://github.com/LeFrenchPOC/Arduino-RGB-Driver/blob/main/LICENSE" target="_blank">
    <img alt="License: GPL--3.0" src="https://img.shields.io/badge/License-GPL--3.0-yellow.svg" />
  </a>
</p>

> Arduino and ESP library to drive RGB LEDs (colors changes and blink) with non-blocking functions

## What is implemented ?
- Non-blocking timings calculation
- Very powerful
- Red Green Blue and intensity

## What is not implemented ?
- Fading

## Install
Use the source files

Install it with platform io : [https://platformio.org/lib/show/13307/RGB%20Driver%20ESP](https://platformio.org/lib/show/13307/RGB%20Driver%20ESP)
```
pio lib install "lefrenchpoc/RGB Driver ESP"
```
or with the `platformio.ini` file :

```
[env:myenv]
platform = espressif8266
framework = arduino

lib_deps = lefrenchpoc/RGB Driver ESP @ ^0.2
```

## Usage

```cpp
#include "rgb.h"

RGB leds({10, 11, 12}); //Red = Pin 10, Green = Pin 11, Blue = Pin 12
ledParam params = {.red = 204, .green = 51, .blue = 255, .intensity = 128, .t_on = 500000, .t_off = 500000}; //Purple color with 50% intensity blink at 2Hz rate

void setup() {
    leds.setLight(&params);
}

void loop() {
    leds.run();
}
```

## Author

👤 **Le French POC**

* Github: [@LeFrenchPOC](https://github.com/LeFrenchPOC)
* Website: [https://www.lefrenchpoc.fr/](https://www.lefrenchpoc.fr/)

## Show your support

Give a ⭐️ if this project helped you!

## 📝 License

Copyright © 2021 [Le French POC](https://github.com/LeFrenchPOC).<br />
This project is [GPL-3.0](https://github.com/LeFrenchPOC/Arduino-RGB-Driver/blob/main/LICENSE) licensed.

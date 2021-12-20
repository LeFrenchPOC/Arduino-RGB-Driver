#include "rgb.h"

RGB leds({10, 11, 12}); //Red = Pin 10, Green = Pin 11, Blue = Pin 12
ledParam params = {.red = 204, .green = 51, .blue = 255, .intensity = 128, .t_on = 500000, .t_off = 500000}; //Purple color with 50% intensity blink at 2Hz rate

void setup() {
    leds.setLight(&params);
}

void loop() {
    leds.run();
}

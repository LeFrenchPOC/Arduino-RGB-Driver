/**
 * @file rgb.cpp
 * @author Axel Chabot - Le French POC (axel.chabot@lefrenchpoc.fr)
 * @brief non-blocking library to manage rgb LEDs (for arduino and ESP32/ESP8266)
 * @version 1.0
 * @date 2021-12-07
 */

#if ESP32
#include <esp32-hal.h>
#endif
#include "rgb.h"

/**
 * @brief Construct a new RGB::RGB object
 * 
 * @param rgbPins array of the pins no
 * @param rChannel red color
 * @param gChannel green color
 * @param bChannel blue color
 */
RGB::RGB(std::array<uint8_t, 3> rgbPins, uint8_t rChannel, uint8_t gChannel, uint8_t bChannel) {
    this->m_channels = {rChannel, gChannel, bChannel};
    this->m_pins = rgbPins;
    this->timeIndex = micros();
    for (uint8_t i = 0; i < 3; i++) {
        #if ESP32
        ledcSetup(this->m_channels[i], 10000, 10);
        ledcAttachPin(rgbPins[i], this->m_channels[i]);
        #elif ESP8266
        pinMode(rgbPins[i], OUTPUT);
        analogWriteFreq(10000);
        analogWriteResolution(10);
        #endif
    }
    stopLight();
}

/**
 * @brief Destroy the RGB::RGB object
 */
RGB::~RGB() {
    #if ESP32
    for(uint8_t pin: this->m_pins) {
        ledcDetachPin(pin);
    }
    #elif ESP8266
    for(uint8_t pin: this->m_pins) {
	analogWrite(pin, 0);
    }
    #endif
}

/**
 * @brief update the timing and the colors of the rgb led
 */
void RGB::run() {
    updateClock();
    updateLight();
}

/**
 * @brief Set led parameters with new parameters
 * @param param new parameters
 */
void RGB::setLight(ledParam *param) {
    if ((param->red != this->currentParam.red) || (param->green != this->currentParam.green) || (param->blue != this->currentParam.blue) || (param->intensity != this->currentParam.intensity) || (param->t_on != this->currentParam.t_on) || (param->t_off != this->currentParam.t_off)) {
        this->currentParam = {param->red, param->green, param->blue, param->intensity, param->t_on, param->t_off};
        this->m_color[0] = EIGHTB_COLOR_INTENS_TO_TENB(this->currentParam.red, this->currentParam.intensity);
        this->m_color[1] = EIGHTB_COLOR_INTENS_TO_TENB(this->currentParam.green, this->currentParam.intensity);
        this->m_color[2] = EIGHTB_COLOR_INTENS_TO_TENB(this->currentParam.blue, this->currentParam.intensity);
        this->enable = true;

        this->nextChange = this->now + this->currentParam.t_on;
        this->lastState = true;
        updateParams(this->m_color);
    }
}

/**
 * @brief Turn off the leds
 * 
 */
void RGB::stopLight() {
    this->enable = false;
    this->lastState = false;
    this->currentParam.red = 0;
    this->currentParam.green = 0;
    this->currentParam.blue = 0;
    this->currentParam.intensity = 0;
    updateParams({0,0,0});
}

/**
 * @brief Update timings
 */
void RGB::updateClock() {
    this->now += (micros() - this->timeIndex);
    this->timeIndex = micros();
}

/**
 * @brief Update led parameters depends of the timings
 */
void RGB::updateLight() {
    if (this->enable) {
        if (this->now >= this->nextChange) {
            if (this->lastState) {
                updateParams({0,0,0});
                this->lastState = false;
                this->nextChange = this->now + this->currentParam.t_off;
            } else {
                updateParams(this->m_color);
                this->lastState = true;
                this->nextChange = this->now + this->currentParam.t_on;
            }
        }
    }
}

/**
 * @brief Write led colors
 * @param newColors array of rgb colors
 */
void RGB::updateParams(std::array<uint16_t, 3> newColors) {
    for (uint8_t i = 0; i < 3; i++) {
        if (newColors[i] != this->lastColor[i]) {
            #if ESP32
            ledcWrite(this->m_channels[i], newColors[i]);
            #elif ESP8266
            analogWrite(this->m_pins[i], newColors[i]);
            #endif
            this->lastColor[i] = newColors[i];
        }
    }
}

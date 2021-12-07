/**
 * @file rgb.h
 * @author Axel Chabot - Le French POC (axel.chabot@lefrenchpoc.fr)
 * @brief Header of rgb.cpp
 * @version 1.0
 * @date 2021-12-07
 */

#ifndef RGB_LED_H
#define RGB_LED_H

#include <array>
#include <Arduino.h>

#if ESP32 || ESP8266
#define EIGHTB_COLOR_INTENS_TO_TENB(color,intens)       ((uint16_t)((float)map(color, 0, 255, 0, 1023)*((float)intens/255)))
#elif
#define EIGHTB_COLOR_INTENS_TO_TENB(color,intens)       ((uint16_t)((float)color*((float)intens/255)))
#endif

/**
 * @brief Structure of LEDs parameters
 */
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t intensity;
    uint32_t t_on; //in us
    uint32_t t_off; //in us
} ledParam;

class RGB {
public:
    RGB(std::array<uint8_t, 3> rgbPins, uint8_t rChannel = 0, uint8_t gChannel = 1, uint8_t bChannel = 2);

    ~RGB();

    void run();

    void setLight(ledParam *param);

    void stopLight();

private:
    std::array<uint8_t, 3> m_pins;
    std::array<uint8_t, 3> m_channels;
    uint32_t now;
    uint32_t timeIndex;
    uint32_t nextChange;
    std::array<uint16_t, 3> m_color;
    std::array<uint16_t, 3> lastColor;
    bool lastState;
    ledParam currentParam;
    bool enable;

    void updateClock();

    void updateLight();

    void updateParams(std::array<uint16_t, 3> newColors);
};

#endif
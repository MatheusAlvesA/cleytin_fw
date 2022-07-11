#ifndef CLEYTIN_ENGINE_H
#define CLEYTIN_ENGINE_H

#include "esp_system.h"
#include "cleytin_commons.h"

#define LCD_CLOCK_PIN GPIO_NUM_19
#define LCD_DATA_PIN GPIO_NUM_18

class CleytinEngine {
public:
    CleytinEngine();

private:
    spi_device_handle_t spi;
    void syncLCD();
    void sendByteToLCD(uint8_t byte);
};

#endif

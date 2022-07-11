#include "cleytin_engine.h"

CleytinEngine::CleytinEngine()
{
    cleytin_set_gpio_pin(LCD_CLOCK_PIN, CLEYTIN_GPIO_MODE_OUTPUT, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(LCD_DATA_PIN, CLEYTIN_GPIO_MODE_OUTPUT, GPIO_INTR_DISABLE);

    //this->sendByteToLCD(0x30);
    //this->sendByteToLCD(0x30);
    this->sendByteToLCD(0x01);
    cleytin_delay(2);
    this->sendByteToLCD(0x06);
    this->sendByteToLCD(0x0F);

    while(true) {
        this->sendByteToLCD(0x0F);
        cleytin_delay(500);
    }
}

void CleytinEngine::syncLCD() {
    gpio_set_level(LCD_DATA_PIN, 1);
    gpio_set_level(LCD_CLOCK_PIN, 0);

    for(int8_t i = 0; i < 5; i++) {
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 1);
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 0);
    }

    gpio_set_level(LCD_DATA_PIN, 0);

    for(int8_t i = 0; i < 3; i++) {
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 1);
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 0);
    }
}

void CleytinEngine::sendByteToLCD(uint8_t byte) {
    this->syncLCD();
    gpio_set_level(LCD_CLOCK_PIN, 0);
    uint8_t part = (byte & 0xF0);
    for(int8_t i = 7; i >= 0; i--) {
        gpio_set_level(LCD_DATA_PIN, part & (1 << i));
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 1);
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 0);
    }

    part = (byte << 4);
    for(int8_t i = 7; i >= 0; i--) {
        gpio_set_level(LCD_DATA_PIN, part & (1 << i));
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 1);
        cleytin_delay(1);
        gpio_set_level(LCD_CLOCK_PIN, 0);
    }
}

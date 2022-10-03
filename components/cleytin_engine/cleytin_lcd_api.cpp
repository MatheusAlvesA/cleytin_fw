#include "cleytin_lcd_api.h"

void CleytinLCDAPI::init()
{
    cleytin_set_gpio_pin(LCD_CLOCK_PIN, CLEYTIN_GPIO_MODE_OUTPUT, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(LCD_DATA_PIN, CLEYTIN_GPIO_MODE_OUTPUT, GPIO_INTR_DISABLE);

    this->dataMode = false;
    this->sendByteToLCD(LCD_CMD_BASIC_SET, true);
    this->sendByteToLCD(LCD_CMD_BASIC_SET, true);
    this->sendByteToLCD(LCD_CMD_CLS, true);
    cleytin_delay(2);
    this->sendByteToLCD(LCD_CMD_ON, true);
    this->sendByteToLCD(LCD_CMD_EXTENDED_SET, true);
    cleytin_delay(10);
    this->sendByteToLCD(LCD_CMD_GRAPH_MODE, true);
    gpio_set_level(LCD_CLOCK_PIN, 0);
}

void CleytinLCDAPI::pulseClock() {
    gpio_set_level(LCD_CLOCK_PIN, 1);
    esp_rom_delay_us(1);
    gpio_set_level(LCD_CLOCK_PIN, 0);
}

void CleytinLCDAPI::prepareCommandLCD() {
    gpio_set_level(LCD_DATA_PIN, 1);
    for(int8_t i = 0; i < 5; i++) {
        this->pulseClock();
    }

    gpio_set_level(LCD_DATA_PIN, 0);
    for(int8_t i = 0; i < 3; i++) {
        this->pulseClock();
    }
    this->dataMode = false;
}

void CleytinLCDAPI::prepareDataLCD() {
    if(this->dataMode) {
        return;
    }

    gpio_set_level(LCD_DATA_PIN, 1);
    for(int8_t i = 0; i < 5; i++) {
        this->pulseClock();
    }

    gpio_set_level(LCD_DATA_PIN, 0);
    this->pulseClock();

    gpio_set_level(LCD_DATA_PIN, 1);
    this->pulseClock();

    gpio_set_level(LCD_DATA_PIN, 0);
    this->pulseClock();
    this->dataMode = true;
}

void CleytinLCDAPI::sendByteToLCD(uint8_t byte, bool isCommand) {
    if(isCommand) {
        this->prepareCommandLCD();
    } else {
        this->prepareDataLCD();
    }

    uint8_t part = (byte & 0xF0);
    for(int8_t i = 7; i >= 0; i--) {
        gpio_set_level(LCD_DATA_PIN, part & (1 << i));
        this->pulseClock();
    }

    part = (byte << 4);
    for(int8_t i = 7; i >= 0; i--) {
        gpio_set_level(LCD_DATA_PIN, part & (1 << i));
        this->pulseClock();
    }
}

void CleytinLCDAPI::renderBuffer(uint8_t *buf) {
    for(uint8_t i = 0; i < 32; i++) {
        this->sendByteToLCD(128 + i, true); // Posição y
        this->sendByteToLCD(128, true);     // Posição x
        for(uint8_t j = 0; j < 16; j++) { // Desenhando na linha com offset 0
            uint8_t byte = buf[(i*16) + j];
            this->sendByteToLCD(byte, false);
        }
        for(uint8_t j = 0; j < 16; j++) { // Desenhando na linha com offset 32
            uint8_t byte = buf[((i + 32)*16) + j];
            this->sendByteToLCD(byte, false);
        }
    }
}

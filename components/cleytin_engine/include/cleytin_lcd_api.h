#ifndef CLEYTIN_LCD_API_H
#define CLEYTIN_LCD_API_H

#include "esp_system.h"
#include "cleytin_commons.h"

#define LCD_CLOCK_PIN GPIO_NUM_19
#define LCD_DATA_PIN GPIO_NUM_18

#define LCD_CMD_CLS 0x01
#define LCD_CMD_ON 0x0C
#define LCD_CMD_BASIC_SET    0x30
#define LCD_CMD_EXTENDED_SET 0x34
#define LCD_CMD_GRAPH_MODE 0x36

#define LCD_WIDTH_PX 128
#define LCD_HEIGHT_PX 64

class CleytinLCDAPI {
public:
    void init();
    void renderBuffer(uint8_t *buf);

private:
    spi_device_handle_t spi;
    bool dataMode;
    void prepareCommandLCD();
    void prepareDataLCD();
    void pulseClock();
    void sendByteToLCD(uint8_t byte, bool isCommand);
};

#endif

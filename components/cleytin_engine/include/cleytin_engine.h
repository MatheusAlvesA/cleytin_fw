#ifndef CLEYTIN_ENGINE_H
#define CLEYTIN_ENGINE_H

#include "esp_system.h"
#include <stdio.h>
#include "cleytin_lcd_api.h"

class CleytinEngine {
public:
    CleytinEngine();
    ~CleytinEngine();

private:
    CleytinLCDAPI api;
    uint8_t *buff;
};

#endif

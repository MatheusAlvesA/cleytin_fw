#ifndef CLEYTIN_CONTROLS_H
#define CLEYTIN_CONTROLS_H

#include "esp_system.h"
#include "cleytin_commons.h"

#define CLEYTIN_BTN_UP GPIO_NUM_21
#define CLEYTIN_BTN_RIGHT GPIO_NUM_22
#define CLEYTIN_BTN_DOWN GPIO_NUM_23
#define CLEYTIN_BTN_LEFT GPIO_NUM_25

#define CLEYTIN_BTN_FUNC GPIO_NUM_33
#define CLEYTIN_BTN_A GPIO_NUM_26
#define CLEYTIN_BTN_B GPIO_NUM_37
#define CLEYTIN_BTN_C GPIO_NUM_32


class CleytinControls {
public:
    CleytinControls();
    bool getUp();
    bool getRight();
    bool getDown();
    bool getLeft();
    bool getStart();
    bool getA();
    bool getB();
    bool getC();

private:
    bool up;
};

#endif

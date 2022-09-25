#include "cleytin_controls.h"

CleytinControls::CleytinControls() {
    cleytin_set_gpio_pin(CLEYTIN_BTN_UP, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_RIGHT, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_DOWN, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_LEFT, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);

    //cleytin_set_gpio_pin(CLEYTIN_BTN_FUNC, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    //cleytin_set_gpio_pin(CLEYTIN_BTN_A, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    //cleytin_set_gpio_pin(CLEYTIN_BTN_B, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    //cleytin_set_gpio_pin(CLEYTIN_BTN_C, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
}

bool CleytinControls::getUp() {
    int r = gpio_get_level(CLEYTIN_BTN_UP);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getRight() {
    int r = gpio_get_level(CLEYTIN_BTN_RIGHT);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getDown() {
    int r = gpio_get_level(CLEYTIN_BTN_DOWN);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getLeft() {
    int r = gpio_get_level(CLEYTIN_BTN_LEFT);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getStart() {
    int r = gpio_get_level(CLEYTIN_BTN_FUNC);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getA() {
    int r = gpio_get_level(CLEYTIN_BTN_A);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getB() {
    int r = gpio_get_level(CLEYTIN_BTN_B);
    if(r == 0) {
        return true;
    }
    return false;
}

bool CleytinControls::getC() {
    int r = gpio_get_level(CLEYTIN_BTN_C);
    if(r == 0) {
        return true;
    }
    return false;
}

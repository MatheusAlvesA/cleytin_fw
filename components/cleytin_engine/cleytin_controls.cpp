#include "cleytin_controls.h"

CleytinControls::CleytinControls() {
    cleytin_set_gpio_pin(CLEYTIN_BTN_UP, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_RIGHT, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_DOWN, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_LEFT, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);

    cleytin_set_gpio_pin(CLEYTIN_BTN_FUNC, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_A, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_B, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    cleytin_set_gpio_pin(CLEYTIN_BTN_C, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
}

bool CleytinControls::readBtnState(gpio_num_t btn, bool debouncing) {
    if(!debouncing) {
        return gpio_get_level(btn) == 0;
    }
    bool r = gpio_get_level(btn) == 0;
    cleytin_delay(1);
    bool r2 = gpio_get_level(btn) == 0;
    return r && r2;
}

bool CleytinControls::getUp(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_UP, debouncing);
}

bool CleytinControls::getRight(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_RIGHT, debouncing);
}

bool CleytinControls::getDown(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_DOWN, debouncing);
}

bool CleytinControls::getLeft(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_LEFT, debouncing);
}

bool CleytinControls::getStart(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_FUNC, debouncing);
}

bool CleytinControls::getA(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_A, debouncing);
}

bool CleytinControls::getB(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_B, debouncing);
}

bool CleytinControls::getC(bool debouncing) {
    return this->readBtnState(CLEYTIN_BTN_C, debouncing);
}

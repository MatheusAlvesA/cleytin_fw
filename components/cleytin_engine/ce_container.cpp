#include "ce_container.h"

CEContainer::CEContainer() {
   this->width = 0;
   this->height = 0;
}

CEContainer::~CEContainer() {/* EMPTY */}

void CEContainer::setRotation(uint16_t rotation) {
   // TODO: Adicionar suporte a rotação
   this->rotation = 0;
}

void CEContainer::setWidth(uint8_t w) {
    this->width = w;
}

void CEContainer::setHeight(uint8_t h) {
    this->height = h;
}

uint8_t CEContainer::getWidth() {
    return this->width;
}

uint8_t CEContainer::getHeight() {
    return this->height;
}

CERenderWindow* CEContainer::getRenderWindow() {
    CERenderWindow *window = this->getDefaultRenderWindow();
    CEPoint *start = new CEPoint((int) this->posX, (int) this->posY);
    CEPoint *end = new CEPoint((int) (this->posX + this->width), (int) (this->posY + this->height));
    window->setPoints(*start, *end);
    delete start;
    delete end;
    return window;
}


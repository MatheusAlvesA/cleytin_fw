#include "ce_rectangle.h"

CERectangle::CERectangle() {
   this->width = 0;
   this->height = 0;
   this->filled = false;
}

void CERectangle::setWidth(uint8_t w) {
    this->width = w;
}

void CERectangle::setHeight(uint8_t h) {
    this->height = h;
}

uint8_t CERectangle::getWidth() {
    return this->width;
}

uint8_t CERectangle::getHeight() {
    return this->height;
}

CERenderWindow* CERectangle::getRenderWindow() {
    CERenderWindow *window = this->getDefaultRenderWindow();
    CEPoint *start = new CEPoint((int) this->posX, (int) this->posY);
    CEPoint *end = new CEPoint((int) (this->posX + this->width), (int) (this->posY + this->height));
    window->setPoints(*start, *end);
    delete start;
    delete end;
    return window;
}

void CERectangle::setFilled(bool fill) {
    this->filled = fill;
}

bool CERectangle::getFilled() {
    return this->filled;
}

bool CERectangle::renderToBuffer(uint8_t *buff, CERenderWindow *window) {
    int startX = window->topLeft->x;
    int startY = window->topLeft->y;
    int endX = window->bottomRight->x;
    int endY = window->bottomRight->y;

    int cursorY = startY;
    bool allPixelRendered = true;
    while(cursorY < endY) {
        int cursorX = startX;
        while (cursorX < endX)
        {
            if(
                !this->setPixel(
                    buff,
                    cursorX,
                    cursorY,
                    this->filled || cursorX == startX || cursorX == (endX - 1) || cursorY == startY || cursorY == (endY - 1)
                )
            ) {
                allPixelRendered = false;
            }
            cursorX++;
        }
        cursorY++;
    }
    
    return allPixelRendered;
}

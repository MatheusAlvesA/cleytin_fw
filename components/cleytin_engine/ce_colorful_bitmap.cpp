#include "ce_colorful_bitmap.h"

CEColorfulBitmap::CEColorfulBitmap() {
   this->width = 0;
   this->height = 0;
   this->buffer = NULL;
   this->alphaColor = 0;
}

CEColorfulBitmap::~CEColorfulBitmap() {
   delete this->buffer;
}

void CEColorfulBitmap::setWidth(unsigned int w) {
    this->width = w;
}

void CEColorfulBitmap::setHeight(unsigned int h) {
    this->height = h;
}

void CEColorfulBitmap::setAlphaColor(uint16_t color) {
    this->alphaColor = color;
}

unsigned int CEColorfulBitmap::getWidth() {
    return this->width;
}

unsigned int CEColorfulBitmap::getHeight() {
    return this->height;
}

uint16_t CEColorfulBitmap::getAlphaColor() {
    return this->alphaColor;
}

CERenderWindow* CEColorfulBitmap::getRenderWindow() {
    CERenderWindow *window = this->getDefaultRenderWindow();
    CEPoint *start = new CEPoint((int) this->posX, (int) this->posY);
    CEPoint *end = new CEPoint((int) (this->posX + this->width), (int) (this->posY + this->height));
    window->setPoints(start, end);
    delete start;
    delete end;
    return window;
}

void CEColorfulBitmap::setBuffer(uint16_t *buffer) {
    this->buffer = buffer;
}

uint16_t *CEColorfulBitmap::getBuffer() {
    return this->buffer;
}

bool CEColorfulBitmap::renderToCanvas(CECanvas *canvas, CERenderWindow *window) {
    int startX = window->topLeft->x;
    int startY = window->topLeft->y;
    int endX = window->bottomRight->x;
    int endY = window->bottomRight->y;

    unsigned int cursorY = startY;
    unsigned int internalCursorY = 0;
    bool allPixelRendered = true;
    while(cursorY < endY) {
        unsigned int cursorX = startX;
        unsigned int internalCursorX = 0;
        while (cursorX < endX)
        {
            unsigned int index = internalCursorX + (internalCursorY * this->getWidth());
            if(
                !this->setPixel(
                    canvas,
                    cursorX,
                    cursorY,
                    (this->buffer[index] != this->alphaColor)
                        ? this->rgb565ToColor(this->buffer[index])
                        : canvas->getBackgroundColor()
                )
            ) {
                allPixelRendered = false;
            }
            cursorX++;
            internalCursorX++;
        }
        cursorY++;
        internalCursorY++;
    }
    
    return allPixelRendered;
}

CEColor CEColorfulBitmap::rgb565ToColor(const uint16_t raw) {
    CEColor r = {0,0,0};

    r.red = (uint8_t) ((raw >> 11) << 3);      // Primeiros 5 bits são o vermelho
    r.green = (uint8_t) ((raw >> 5) << 2);    // Bits 6 até 11 são o verde
    r.blue = (uint8_t) (raw << 3);            // Bits 12 até 16 são o azul

    printf("R(%d) G(%d) B(%d)\n", r.red, r.green, r.blue);

    return r;
}

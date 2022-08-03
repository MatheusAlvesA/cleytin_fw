#ifndef CE_BITMAP_H
#define CE_BITMAP_H

#include "cleytin_engine.h"

class CEBitmap : public CEGraphicObject {
public:
    CEBitmap();
    ~CEBitmap();
    void setWidth(uint8_t w);
    void setHeight(uint8_t h);
    void setBuffer(uint8_t *buffer);
    uint8_t getWidth();
    uint8_t getHeight();
    uint8_t *getBuffer();

    CERenderWindow* getRenderWindow();
    bool renderToBuffer(uint8_t *buff, CERenderWindow *window);

protected:
    uint8_t width;
    uint8_t height;
    uint8_t *buffer;
};

#endif

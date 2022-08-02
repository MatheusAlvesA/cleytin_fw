#ifndef CE_RECTANGLE_H
#define CE_RECTANGLE_H

#include "cleytin_engine.h"

class CERectangle : public CEGraphicObject {
public:
    CERectangle();
    void setWidth(uint8_t w);
    void setHeight(uint8_t h);
    void setFilled(bool fill);
    bool getFilled();
    uint8_t getWidth();
    uint8_t getHeight();

    CERenderWindow* getRenderWindow();
    bool renderToBuffer(uint8_t *buff, CERenderWindow *window);

protected:
    uint8_t width;
    uint8_t height;
    bool filled;
};

#endif

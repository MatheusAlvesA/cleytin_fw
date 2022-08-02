#ifndef CE_CIRCLE_H
#define CE_CIRCLE_H

#include "cleytin_engine.h"

class CECircle : public CEGraphicObject {
public:
    CECircle();
    void setRadius(uint8_t r);
    void setFilled(bool fill);
    void setRotation(uint16_t rotation);

    uint8_t getRadius();
    bool getFilled();
    virtual uint16_t getRotation();

    CERenderWindow* getRenderWindow();
    bool renderToBuffer(uint8_t *buff, CERenderWindow *window);

protected:
    uint8_t radius;
    bool filled;
};
#endif

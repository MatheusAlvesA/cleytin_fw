#ifndef CE_CONTAINER_H
#define CE_CONTAINER_H

#include "cleytin_engine.h"

class CEContainer : public CEGraphicObject {
public:
    CEContainer();
    ~CEContainer();
    void setWidth(uint8_t w);
    void setHeight(uint8_t h);
    uint8_t getWidth();
    uint8_t getHeight();

    unsigned int addObject(CEGraphicObject *obj);
    bool removeObject(CEGraphicObject *obj);
    bool removeObjectAt(size_t index);
    CEGraphicObject* getObjectAt(size_t index);
    size_t getObjectIndex(CEGraphicObject* obj);
    size_t getObjectsCount();

    void setRotation(uint16_t rotation);
    void setMirrored(bool mirrored);
    void setNegative(bool negative);

    CERenderWindow* getRenderWindow();
    bool renderToBuffer(uint8_t *buff, CERenderWindow *window);

protected:
    uint8_t width;
    uint8_t height;
    std::vector <CEGraphicObject*> *objects;
};

#endif

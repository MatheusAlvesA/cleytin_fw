#ifndef CLEYTIN_ENGINE_H
#define CLEYTIN_ENGINE_H

#include <vector>
#include <algorithm>
#include <math.h>
#include "esp_system.h"
#include "cleytin_lcd_api.h"

#define PI 3.142857

class CEPoint {
public:
    uint8_t x;
    uint8_t y;

    CEPoint(uint8_t x, uint8_t y);
    bool operator==(const CEPoint &dot);
};


class CERenderWindow {
public:
    CERenderWindow(const CEPoint &start, const CEPoint &end);
    ~CERenderWindow();
    CEPoint *start;
    CEPoint *end;

    CEPoint* getCenterPoint();
};


class CEGraphicObject {
public:
    CEGraphicObject();
    virtual CERenderWindow* getRenderWindow() = 0;
    virtual bool renderToBuffer(uint8_t *buff);
    virtual bool renderToBuffer(uint8_t *buff, CERenderWindow *window) = 0;
    // Setters
    virtual void setVisible(bool visible);
    virtual void setColisionEnabled(bool enabled);
    virtual void setPriority(uint8_t priority);
    virtual void setPosX(uint8_t x);
    virtual void setPosY(uint8_t y);
    virtual void setPos(uint8_t x, uint8_t y);
    virtual void setRotation(uint16_t rotation);
    // Getters
    virtual bool getVisible();
    virtual bool getColisionEnabled();
    virtual uint8_t getPriority();
    virtual uint8_t getPosX();
    virtual uint8_t getPosY();
    virtual uint16_t getRotation();

protected:
    bool visible;
    bool colisionEnabled;
    uint8_t priority;
    uint8_t posX;
    uint8_t posY;
    uint16_t rotation;

    bool setPixel(uint8_t *buff, uint8_t x, uint8_t y, bool state);
    bool rotatePixel(uint8_t &x, uint8_t &y, double rot);
};


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


class CleytinEngine {
public:
    CleytinEngine();
    ~CleytinEngine();

    unsigned int addObject(CEGraphicObject *obj);
    bool removeObject(CEGraphicObject *obj);
    bool removeObjectAt(size_t index);
    CEGraphicObject* getObjectAt(size_t index);
    size_t getObjectsCount();
    void renderToBuffer();
    uint8_t* getBuffer();
    void sendBufferToLCD(uint8_t *buff);
    void render();

private:
    CleytinLCDAPI api;
    uint8_t *buff;
    std::vector <CEGraphicObject*> objects;
};

#endif

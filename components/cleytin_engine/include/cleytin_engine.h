#ifndef CLEYTIN_ENGINE_H
#define CLEYTIN_ENGINE_H

#include <stdio.h>
#include <vector>
#include <algorithm>
#include "esp_system.h"
#include "cleytin_lcd_api.h"

class CEDot {
public:
    uint8_t x;
    uint8_t y;

    CEDot(uint8_t x, uint8_t y);
    bool operator==(const CEDot &dot);
};


class CERenderWindow {
public:
    CERenderWindow(const CEDot &start, const CEDot &end);
    ~CERenderWindow();
    CEDot *start;
    CEDot *end;
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
    // Getters
    virtual bool getVisible();
    virtual bool getColisionEnabled();
    virtual uint8_t getPriority();
    virtual uint8_t getPosX();
    virtual uint8_t getPosY();

protected:
    bool visible;
    bool colisionEnabled;
    uint8_t priority;
    uint8_t posX;
    uint8_t posY;

    bool setPixel(uint8_t *buff, uint8_t x, uint8_t y, bool state);
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

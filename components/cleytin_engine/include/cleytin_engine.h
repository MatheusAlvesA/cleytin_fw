#ifndef CLEYTIN_ENGINE_H
#define CLEYTIN_ENGINE_H

#include <vector>
#include <algorithm>
#include "esp_system.h"
#include "cleytin_lcd_api.h"

#include <math.h>

#define PI 3.142857

class CEPoint {
public:
    int x;
    int y;

    CEPoint(int x, int y);
    bool operator==(const CEPoint &dot);

    void rotate(CEPoint *rotationCenter, uint16_t degrees);
    CEPoint * clone();
    unsigned int distanceTo(const CEPoint point);
};


class CELine {
public:
    CELine(const CEPoint &start, const CEPoint &end);
    ~CELine();
    CEPoint *start;
    CEPoint *end;

    int calculateSideOfPoint(CEPoint *point);
};

class CERenderWindow {
public:
    CERenderWindow(const CEPoint *start, const CEPoint *end);
    ~CERenderWindow();
    CEPoint *topLeft;
    CEPoint *topRight;
    CEPoint *bottomLeft;
    CEPoint *bottomRight;

    void setPoints(const CEPoint *start, const CEPoint *end);
    void setMaxX(uint8_t x);
    void setMaxY(uint8_t y);

    CEPoint* getCenterPoint();
    CELine* getTopLine();
    CELine* getBottomLine();
    CELine* getLeftLine();
    CELine* getRightLine();
    size_t getHeight();
    size_t getWidth();

    std::vector<CEPoint*>* getAllPoints();

    bool containsPoint(CEPoint *point);
    void expand(uint8_t size);

    void rotate(uint16_t degrees);

private:
    uint8_t maxX;
    uint8_t maxY;
};

class CEGraphicObject {
public:
    CEGraphicObject();
    virtual ~CEGraphicObject();
    virtual CERenderWindow* getDefaultRenderWindow();
    virtual CERenderWindow* getRenderWindow() = 0;
    virtual bool renderToBuffer(uint8_t *buff);
    virtual bool renderToBuffer(uint8_t *buff, CERenderWindow *window) = 0;
    virtual bool containsPoint(CEPoint *point, uint8_t expand = 0);
    virtual bool containsAnyPointsFrom(std::vector<CEPoint *> *points, const uint8_t expand = 0);
    virtual std::vector<CEPoint *> *getAllRenderWindowPoints();
    // Setters
    virtual void setVisible(bool visible);
    virtual void setMirrored(bool mirrored);
    virtual void setNegative(bool negative);
    virtual void setColisionEnabled(bool enabled);
    virtual void setPriority(uint8_t priority);
    virtual void setPosX(uint8_t x);
    virtual void setPosY(uint8_t y);
    virtual void setMaxX(uint8_t x);
    virtual void setMaxY(uint8_t y);
    virtual void setPos(uint8_t x, uint8_t y);
    virtual void setRotation(uint16_t rotation);
    // Getters
    virtual bool getVisible();
    virtual bool getMirrored();
    virtual bool getNegative();
    virtual bool getColisionEnabled();
    virtual uint8_t getPriority();
    virtual uint8_t getPosX();
    virtual uint8_t getPosY();
    virtual uint8_t getMaxX();
    virtual uint8_t getMaxY();
    virtual uint16_t getRotation();
    virtual size_t getRenderWindowHeight();
    virtual size_t getRenderWindowWidth();

protected:
    bool visible;
    bool colisionEnabled;
    bool mirrored;
    bool negative;
    uint8_t priority;
    uint8_t posX;
    uint8_t posY;
    uint8_t maxX;
    uint8_t maxY;
    uint16_t rotation;

    bool setPixel(uint8_t *buff, int x, int y, bool state);
    bool rotatePixel(int &x, int &y, uint16_t rot);
    void mirrorPixel(int &x);
};

class CleytinEngine {
public:
    CleytinEngine();
    ~CleytinEngine();

    unsigned int addObject(CEGraphicObject *obj);
    bool removeObject(CEGraphicObject *obj, bool freeMemory = false);
    bool removeObjectAt(size_t index, bool freeMemory = false);
    void clear(bool freeMemory = false);
    std::vector<size_t>* getCollisionsOn(size_t index);
    CEGraphicObject* getObjectAt(size_t index);
    std::vector<size_t>* getObjectsAt(CEPoint *point);
    size_t getObjectIndex(CEGraphicObject* obj);
    size_t getObjectsCount();
    void renderToBuffer();
    uint8_t* getBuffer();
    void sendBufferToLCD(uint8_t *buff);
    uint64_t render();

private:
    CleytinLCDAPI api;
    uint8_t *buff;
    std::vector <CEGraphicObject*> objects;
};

bool compareObjectPriority(CEGraphicObject *a, CEGraphicObject *b);
void delete_points_vector(std::vector<CEPoint *> *v);

#endif

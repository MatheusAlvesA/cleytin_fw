#include "cleytin_engine.h"

bool compareObjectPriority(CEGraphicObject *a, CEGraphicObject *b) {
    return a->getPriority() > b->getPriority();
}

/* CleytinEngine */

CleytinEngine::CleytinEngine()
{
    this->buff = new uint8_t[(128 * 64) / 8]; // 128 por 64 bits de resolução
    memset(this->buff, 0, (128 * 64) / 8);
    this->api.init();
    this->api.renderBuffer(this->buff);
}

CleytinEngine::~CleytinEngine()
{
    delete this->buff;
}

unsigned int CleytinEngine::addObject(CEGraphicObject *obj) {
    this->objects.push_back(obj);
    std::sort(this->objects.begin(), this->objects.end(), compareObjectPriority);
    return (unsigned int) this->objects.size();
}

bool CleytinEngine::removeObject(CEGraphicObject *obj) {
    size_t index = this->objects.size();
    for (size_t i = 0; i < this->objects.size(); i++) {
        if(this->objects[i] == obj) {
            index = i;
            break;
        }
    }

    return this->removeObjectAt(index);
}

bool CleytinEngine::removeObjectAt(size_t index) {
    if(index >= this->objects.size()) {
        return false;
    }

    while(index < this->objects.size()-1) {
        this->objects[index] = this->objects[index+1];
        index++;
    }
    this->objects.pop_back();
    return true;
}

size_t CleytinEngine::getObjectsCount() {
    return this->objects.size();
}

CEGraphicObject* CleytinEngine::getObjectAt(size_t index) {
    if(index >= this->objects.size()) {
        return NULL;
    }

    return this->objects[index];
}

void CleytinEngine::renderToBuffer() {
    memset(this->buff, 0, (128 * 64) / 8);
    for (size_t i = 0; i < this->objects.size(); i++) {
        this->objects[i]->renderToBuffer(this->buff);
    }
}

void CleytinEngine::sendBufferToLCD(uint8_t *buff) {
    this->api.renderBuffer(buff);
}

void CleytinEngine::render() {
    this->renderToBuffer();
    this->sendBufferToLCD(this->buff);
}

uint8_t* CleytinEngine::getBuffer() {
    return this->buff;
}


/* CEDot */

CEDot::CEDot(uint8_t x, uint8_t y) {
    this->x = x;
    this->y = y;
}

bool CEDot::operator==(const CEDot &dot) {
    return this->x == dot.x && this->y == dot.y;
}

/* CERenderWindow */

CERenderWindow::CERenderWindow(const CEDot &start, const CEDot &end) {
    this->start = new CEDot(start.x, start.y);
    this->end = new CEDot(end.x, end.y);
}

CERenderWindow::~CERenderWindow() {
    delete this->start;
    delete this->end;
}

/* CEGraphicObject */

CEGraphicObject::CEGraphicObject() {
    this->colisionEnabled = true;
    this->visible = true;
    this->priority = 0;
    this->posX = 0;
    this->posY = 0;
}

void CEGraphicObject::setVisible(bool visible) {
    this->visible = visible;
}

void CEGraphicObject::setColisionEnabled(bool enabled) {
    this->colisionEnabled = enabled;
}

void CEGraphicObject::setPriority(uint8_t priority) {
    this->priority = priority;
}

void CEGraphicObject::setPosX(uint8_t posX) {
    this->posX = posX;
}

void CEGraphicObject::setPosY(uint8_t posY) {
    this->posY = posY;
}

void CEGraphicObject::setPos(uint8_t x, uint8_t y) {
    this->posX = x;
    this->posY = y;
}

bool CEGraphicObject::renderToBuffer(uint8_t *buff) {
    return this->renderToBuffer(buff, this->getRenderWindow());
}

bool CEGraphicObject::getVisible() {
    return this->visible;
}

bool CEGraphicObject::getColisionEnabled() {
    return this->colisionEnabled;
}

uint8_t CEGraphicObject::getPriority() {
    return this->priority;
}

uint8_t CEGraphicObject::getPosX() {
    return this->posX;
}

uint8_t CEGraphicObject::getPosY() {
    return this->posY;
}

bool CEGraphicObject::setPixel(uint8_t *buff, uint8_t x, uint8_t y, bool state) {
    if(y >= LCD_HEIGHT_PX || x >= LCD_WIDTH_PX) {
        return false;
    }

    unsigned int bitPos = x + (y * LCD_WIDTH_PX);
    unsigned int bytePos = bitPos / 8;
    unsigned int bitOffset = bitPos % 8;
    if(state) {
        buff[bytePos] |= 1 << (7 - bitOffset);
    } else {
        buff[bytePos] &= ~(1 << (7 - bitOffset));
    }

    return true;
}


/* CERectangle */

CERectangle::CERectangle() {
   this->width = 0;
   this->height = 0;
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
    CEDot *start = new CEDot(this->posX, this->posY);
    CEDot *end = new CEDot(this->posX + this->width, this->posY + this->height);
    CERenderWindow *window = new CERenderWindow(*start, *end);
    delete start;
    delete end;
    return window;
}

bool CERectangle::renderToBuffer(uint8_t *buff, CERenderWindow *window) {
    uint8_t startX = window->start->x;
    uint8_t startY = window->start->y;
    uint8_t endX = window->end->x;
    uint8_t endY = window->end->y;
    delete window;

    uint8_t cursorY = startY;
    while(cursorY <= endY) {
        uint8_t cursorX = startX;
        while (cursorX <= endX)
        {
            if(!this->setPixel(buff, cursorX, cursorY, true)) {
                return false;
            }
            cursorX++;
        }
        cursorY++;
    }
    
    return true;
}

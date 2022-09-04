#include "ce_container.h"

inline bool compareObjectPriority(CEGraphicObject *a, CEGraphicObject *b) {
    return a->getPriority() < b->getPriority();
}

CEContainer::CEContainer() {
   this->width = 0;
   this->height = 0;
   this->objects = new std::vector <CEGraphicObject*>();
}

CEContainer::~CEContainer() {
    for (size_t i = 0; i < this->objects->size(); i++) {
        delete this->objects->at(i);
    }
    delete this->objects;
}

// TODO Adicionar suporte para os métodos setRotation, setMirrored e setNegative
void CEContainer::setRotation(uint16_t rotation) {
   this->rotation = 0;
}

void CEContainer::setMirrored(bool mirrored) {
    this->mirrored = false;
}

void CEContainer::setNegative(bool negative) {
    this->negative = false;
}


unsigned int CEContainer::addObject(CEGraphicObject *obj) {
    this->objects->push_back(obj);
    std::sort(this->objects->begin(), this->objects->end(), compareObjectPriority);
    return (unsigned int) this->objects->size();
}

bool CEContainer::removeObject(CEGraphicObject *obj) {
    return this->removeObjectAt(this->getObjectIndex(obj));
}

bool CEContainer::removeObjectAt(size_t index) {
    if(index >= this->objects->size()) {
        return false;
    }

    while(index < this->objects->size()-1) {
        (*this->objects)[index] = (*this->objects)[index+1];
        index++;
    }
    this->objects->pop_back();
    return true;
}

size_t CEContainer::getObjectsCount() {
    return this->objects->size();
}

CEGraphicObject* CEContainer::getObjectAt(size_t index) {
    if(index >= this->objects->size()) {
        return NULL;
    }

    return (*this->objects)[index];
}

size_t CEContainer::getObjectIndex(CEGraphicObject* obj) {
    for (size_t i = 0; i < this->objects->size(); i++)
    {
        if(obj == (*this->objects)[i]) {
            return i;
        }
    }
    return this->objects->size()+1;
}

void CEContainer::setWidth(uint8_t w) {
    this->width = w;
}

void CEContainer::setHeight(uint8_t h) {
    this->height = h;
}

uint8_t CEContainer::getWidth() {
    return this->width;
}

uint8_t CEContainer::getHeight() {
    return this->height;
}

CERenderWindow* CEContainer::getRenderWindow() {
    CERenderWindow *window = this->getDefaultRenderWindow();
    CEPoint *start = new CEPoint((int) this->posX, (int) this->posY);
    CEPoint *end = new CEPoint((int) (this->posX + this->width), (int) (this->posY + this->height));
    window->setPoints(*start, *end);
    delete start;
    delete end;
    return window;
}

bool CEContainer::renderToBuffer(uint8_t *buff, CERenderWindow *window) {
    bool r = true;
    uint8_t bkpX = 0;
    uint8_t bkpY = 0;
    uint offsetX = window->topLeft->x;
    uint offsetY = window->topLeft->y;
    uint maxX = window->bottomRight->x;
    uint maxY = window->bottomRight->y;
    for (size_t i = 0; i < this->objects->size(); i++) {
        CEGraphicObject *obj = this->objects->at(i);
        bkpX = obj->getPosX();
        bkpY = obj->getPosY();
        obj->setPos(bkpX + offsetX, bkpY + offsetY);
        obj->setMaxX(maxX);
        obj->setMaxY(maxY);
        if(!obj->renderToBuffer(buff)) {
            r = false;
        }
        obj->setPos(bkpX, bkpY);
    }
    return r;
}

#include "ce_menu_helper.h"


CEMenuHelper::CEMenuHelper() {
   this->width = LCD_WIDTH_PX;
   this->height = LCD_HEIGHT_PX;
   this->selected = 0;
   this->itemsOffset = 0;
   this->options = new std::vector <CEMenuOption>();
   this->ctrl = new CleytinControls();
   this->selectionMade = false;
   this->btnAState = false;
   this->btnStartState = false;
   this->btnUpState = false;
   this->btnDownState = false;
}

CEMenuHelper::~CEMenuHelper() {
    for (size_t i = 0; i < this->options->size(); i++) {
        delete this->options->at(i).label;
    }
    delete this->options;
    delete this->ctrl;
}

void CEMenuHelper::clearOptions() {
    for (size_t i = 0; i < this->options->size(); i++) {
        delete this->options->at(i).label;
    }
    this->options->clear();
    this->selected = 0;
}

void CEMenuHelper::setRotation(uint16_t rotation) {
   this->rotation = 0; // Sem suporte a rotação
}

void CEMenuHelper::setMirrored(bool mirrored) {
    this->mirrored = false; // Sem suporte a espelhamento
}

void CEMenuHelper::setNegative(bool negative) {
    this->negative = false; // Sem suporte a negativo
}

void CEMenuHelper::addOption(const char *label, uint id) {
    size_t labelSize = 0;
    for (labelSize = 0; *(label+labelSize) != '\0'; labelSize++);
    char *copyLabel = (char *) malloc(labelSize+1);
    for (size_t i = 0; i < labelSize; i++)
    {
        *(copyLabel + i) = *(label + i);
    }
    *(copyLabel + labelSize) = '\0';
    
    this->options->push_back({copyLabel, id});
}

void CEMenuHelper::setWidth(uint8_t w) {
    this->width = w;
}

void CEMenuHelper::setHeight(uint8_t h) {
    this->height = h;
}

uint8_t CEMenuHelper::getWidth() {
    return this->width;
}

uint8_t CEMenuHelper::getHeight() {
    return this->height;
}

uint CEMenuHelper::getSelected() {
    if(this->options->size() <= 0) {
        return 0;
    }
    return this->options->at(this->selected).id;
}

bool CEMenuHelper::handleControls() {
    if(this->selectionMade) {
        return true;
    }

    bool r = this->ctrl->getA();
    if(r) {
        this->selectionMade = true;
        return true;
    }

    r = this->ctrl->getUp();
    if(r && !this->btnUpState) {
        this->moveCursorUp();
        this->btnUpState = true;
        return false;
    } else if(!r) {
        this->btnUpState = false;
    }

    r = this->ctrl->getDown();
    if(r && !this->btnDownState) {
        this->moveCursorDown();
        this->btnDownState = true;
        return false;
    } else if(!r) {
        this->btnDownState = false;
    }

    if(this->ctrl->getStart()) {
        this->btnStartState = true;
    }
    return false;
}

bool CEMenuHelper::startPressed() {
    return this->btnStartState;
}

void CEMenuHelper::moveCursorDown() {
    this->selected++;
    if(this->selected >= this->options->size()) {
        this->selected = 0;
        this->itemsOffset = 0;
    } else {
        size_t maxItems = this->getHeight() / FONT_HEIGHT;
        while(this->selected >= (this->itemsOffset + maxItems)) {
            this->itemsOffset++;
        }
    }
}

void CEMenuHelper::moveCursorUp() {
    if(this->selected <= 0) {
        size_t maxItems = this->getHeight() / FONT_HEIGHT;
        this->selected = this->options->size() >= 1 ? this->options->size()-1 : 0;
        this->itemsOffset = 0;
        if(this->options->size() > maxItems) {
            this->itemsOffset = this->options->size() - maxItems;
        }
    } else {
        this->selected--;
        while(this->selected < this->itemsOffset) {
            this->itemsOffset--;
        }
    }
}

CERenderWindow* CEMenuHelper::getRenderWindow() {
    CERenderWindow *window = this->getDefaultRenderWindow();
    CEPoint *start = new CEPoint((int) this->posX, (int) this->posY);
    CEPoint *end = new CEPoint((int) (this->posX + this->width), (int) (this->posY + this->height));
    window->setPoints(start, end);
    delete start;
    delete end;
    return window;
}

bool CEMenuHelper::renderToBuffer(uint8_t *buff, CERenderWindow *window) {
    bool r = true;
    if(!this->renderOptionsToBuffer(buff, window)) {
        r = false;
    }
    if(!this->renderMenuInfoToBuffer(buff, window)) {
        r = false;
    }
    return r;
}

bool CEMenuHelper::renderOptionsToBuffer(uint8_t *buff, CERenderWindow *window) {
    size_t maxItems = this->getHeight() / FONT_HEIGHT;
    CEContainer *c = new CEContainer();
    c->setPositioningStyle(CEPositioningStyle::FLEX_COLUMN);
    c->setAlignY(CEAlign::START);
    c->setAlignX(CEAlign::START);
    c->setHeight(this->getHeight());
    c->setWidth(this->getWidth() - 8); // 8 pixels para as instruções a esquerda do menu
    c->setPos(this->getPosX() + 8, this->getPosY());
    for (size_t i = this->itemsOffset; i < this->options->size() && i < maxItems + this->itemsOffset; i++)
    {
        CEText *txt = new CEText();
        txt->setText(this->options->at(i).label);
        txt->setPriority(i);
        txt->setWrap(false);
        if(i == this->selected) {
            txt->setNegative(true);
        }
        c->addObject(txt);
    }
    bool r = ((CEGraphicObject *)c)->renderToBuffer(buff);
    delete c;
    return r;
}

bool CEMenuHelper::renderMenuInfoToBuffer(uint8_t *buff, CERenderWindow *window) {
    size_t maxItems = this->getHeight() / FONT_HEIGHT;
    CEContainer *c = new CEContainer();
    c->setPositioningStyle(CEPositioningStyle::FLEX_COLUMN);
    c->setAlignY(CEAlign::SPACE_BETWEEN);
    c->setAlignX(CEAlign::CENTER);
    c->setHeight(this->getHeight());
    c->setWidth(8);
    c->setPos(this->getPosX(), this->getPosY());

    if(this->selected >= maxItems) {
        CEBitmap *bmp = new CEBitmap();
        const uint8_t buffStack[] = {0x0, 0x10, 0x38, 0x7C, 0x7C, 0x38, 0x38, 0x38, 0x0, 0x0, 0x0, 0x0};
        uint8_t *buff = (uint8_t *) malloc(8*12);
        for (size_t i = 0; i < 12; i++) {
            *(buff+i) = buffStack[i];
        }
        bmp->setBuffer(buff);
        bmp->setHeight(12);
        bmp->setWidth(8);
        bmp->setPriority(0);
        c->addObject(bmp);
    } else {
        CEContainer *placeholder = new CEContainer();
        placeholder->setWidth(1);
        placeholder->setHeight(12);
        placeholder->setPriority(0);
        c->addObject(placeholder);
    }

    if((this->itemsOffset + maxItems) < this->options->size()) {
        CEBitmap *bmp = new CEBitmap();
        const uint8_t buffStack[] = {0x0, 0x0, 0x0, 0x0, 0x38, 0x38, 0x38, 0x7C, 0x7C, 0x38, 0x10, 0x0};
        uint8_t *buff = (uint8_t *) malloc(8*12);
        for (size_t i = 0; i < 12; i++) {
            *(buff+i) = buffStack[i];
        }
        bmp->setBuffer(buff);
        bmp->setHeight(12);
        bmp->setWidth(8);
        bmp->setPriority(2);
        c->addObject(bmp);
    } else {
        CEContainer *placeholder = new CEContainer();
        placeholder->setWidth(1);
        placeholder->setHeight(12);
        placeholder->setPriority(2);
        c->addObject(placeholder);
    }

    bool r = ((CEGraphicObject *)c)->renderToBuffer(buff);
    delete c;
    return r;
}

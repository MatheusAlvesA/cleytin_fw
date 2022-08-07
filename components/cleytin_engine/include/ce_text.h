#ifndef CE_TEXT_H
#define CE_TEXT_H

#include "cleytin_engine.h"
#include "ce_8x12_font.h"

class CEText : public CEGraphicObject {
public:
    CEText();
    ~CEText();
    void setText(const char *buffer);
    void setCustomFont(CEFont *font);
    void setWrap(bool wrap);
    uint8_t getWidth();
    uint8_t getHeight();

    CERenderWindow* getRenderWindow();
    bool renderToBuffer(uint8_t *buff, CERenderWindow *window);

protected:
    char *text;
    size_t length;
    CEFont *font;
    bool wrap;

    bool renderChar(uint8_t *buff, char c, uint8_t x, uint8_t y);
};

#endif

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
    unsigned int getWidth();
    unsigned int getHeight();

    CERenderWindow* getRenderWindow();
    bool renderToCanvas(CECanvas *canvas, CERenderWindow *window);

protected:
    char *text;
    size_t length;
    CEFont *font;
    bool wrap;

    bool renderChar(CECanvas *canvas, char c, unsigned int x, unsigned int y);
};

#endif

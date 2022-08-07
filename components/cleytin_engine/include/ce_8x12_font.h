#ifndef CE_8X12_FONT_H
#define CE_8X12_FONT_H

#include "ce_font.h"

const uint8_t buff[] = {0x0, 0x0, 0xFF, 0x99, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x0, 0x0};

class CE8x12Font : public CEFont {
public:
    CE8x12Font();
    ~CE8x12Font();
    virtual uint8_t getCharWidth();
    virtual uint8_t getCharHeight();
    virtual uint8_t *getRawPonter();
    virtual unsigned int getPositionOf(char c);
};

#endif

#ifndef CE_FONT_H
#define CE_FONT_H

#include "cleytin_commons.h"

class CEFont {
public:
    virtual ~CEFont();
    virtual uint8_t getCharWidth();
    virtual uint8_t getCharHeight();
    virtual uint8_t *getRawPonter();
    virtual char *parseString(const char *str);
    virtual unsigned int getPositionOf(unsigned char c);
};

#endif

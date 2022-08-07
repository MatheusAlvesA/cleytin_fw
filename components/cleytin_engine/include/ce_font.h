#ifndef CE_FONT_H
#define CE_FONT_H

#include <stdint.h>

class CEFont {
public:
    virtual ~CEFont();
    virtual uint8_t getCharWidth();
    virtual uint8_t getCharHeight();
    virtual uint8_t *getRawPonter();
    virtual unsigned int getPositionOf(char c);
};

#endif

#ifndef CE_MENU_HELPER_H
#define CE_MENU_HELPER_H

#include "cleytin_engine.h"
#include "ce_container.h"
#include "ce_text.h"
#include "ce_bitmap.h"

#define FONT_WIDTH 8
#define FONT_HEIGHT 12

typedef struct {
  const char *label;
  uint id;
} CEMenuOption;

class CEMenuHelper : public CEGraphicObject {
public:
    CEMenuHelper();
    ~CEMenuHelper();
    void setWidth(uint8_t w);
    void setHeight(uint8_t h);
    uint8_t getWidth();
    uint8_t getHeight();
    uint getPreselected();

    void setRotation(uint16_t rotation);
    void setMirrored(bool mirrored);
    void setNegative(bool negative);

    void addOption(const char *label, uint id);
    void clearOptions();

    void moveCursorDown();
    void moveCursorUp();

    CERenderWindow* getRenderWindow();
    bool renderToBuffer(uint8_t *buff, CERenderWindow *window);

protected:
    uint8_t width;
    uint8_t height;
    std::vector <CEMenuOption> *options;
    size_t selected;
    size_t itemsOffset;

    bool renderOptionsToBuffer(uint8_t *buff, CERenderWindow *window);
    bool renderMenuInfoToBuffer(uint8_t *buff, CERenderWindow *window);
};

#endif

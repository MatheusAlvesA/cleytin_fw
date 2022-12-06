#ifndef CE_MENU_HELPER_H
#define CE_MENU_HELPER_H

#include "cleytin_engine.h"
#include "ce_container.h"
#include "ce_text.h"
#include "ce_bitmap.h"
#include "cleytin_controls.h"

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
    void setWidth(unsigned int w);
    void setHeight(unsigned int h);
    unsigned int getWidth();
    unsigned int getHeight();
    uint getSelected();

    void setRotation(uint16_t rotation);
    void setMirrored(bool mirrored);
    void setNegative(bool negative);

    void addOption(const char *label, uint id);
    void clearOptions();

    void moveCursorDown();
    void moveCursorUp();
    bool handleControls();
    bool startPressed();
    void reset();

    CERenderWindow* getRenderWindow();
    bool renderToCanvas(CECanvas *canvas, CERenderWindow *window);

protected:
    CleytinControls *ctrl;
    unsigned int width;
    unsigned int height;
    std::vector <CEMenuOption> *options;
    size_t selected;
    size_t itemsOffset;
    bool selectionMade;
    bool btnStartState;

    bool renderOptionsToCanvas(CECanvas *canvas, CERenderWindow *window);
    bool renderMenuInfoToCanvas(CECanvas *canvas, CERenderWindow *window);
};

#endif

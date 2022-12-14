#ifndef FWFUN_TEST_H
#define FWFUN_TEST_H

#include "cleytin_engine.h"
#include "ce_rectangle.h"
#include "ce_container.h"
#include "ce_text.h"
#include "cleytin_sdcard.h"
#include "cleytin_controls.h"

class FWFUNTest {
public:
    void run(CleytinEngine *engine);

private:
    bool testScreen(CleytinEngine *engine);
    bool testSerial(CleytinEngine *engine);
    bool testSDCard(CleytinEngine *engine);
    bool testButtons(CleytinEngine *engine);
    void testButton(CleytinEngine *engine, const char *label, gpio_num_t btn);
    void showResults(CleytinEngine *engine, bool screen, bool serial, bool SDCard, bool buttons);
    void putLabelInContainer(CEContainer *container, const char *label, uint8_t pos, const CEColor color = {0,0,0});
};

#endif

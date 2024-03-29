#include "fwfun_test.h"

void FWFUNTest::run(CleytinEngine *engine) {
    engine->clear();
    engine->loopAndRender();
    bool screen = this->testScreen(engine);
    engine->clear();
    engine->loopAndRender();
    bool serial = this->testSerial(engine);
    engine->clear();
    engine->loopAndRender();
    bool sdcard = this->testSDCard(engine);
    engine->clear();
    engine->loopAndRender();
    bool buttons = this->testButtons(engine);
    engine->clear();
    engine->loopAndRender();

    this->showResults(engine, screen, serial, sdcard, buttons);
}

bool FWFUNTest::testScreen(CleytinEngine *engine) {
    CERectangle *rect = new CERectangle();
    rect->setHeight(LCD_HEIGHT_PIXELS);
    rect->setFilled(true);
    rect->setPos(0, 0);
    engine->addObject(rect);
    for (unsigned int i = 0; i <= LCD_WIDTH_PIXELS; i += 5) {
        rect->setWidth(i);
        engine->loopAndRender();
        cleytin_delay(20);
    }
    for (unsigned int i = 0; i <= LCD_WIDTH_PIXELS; i += 5) {
        rect->setPosX(i);
        engine->loopAndRender();
        cleytin_delay(20);
    }
    engine->removeObject(rect, true);
    return true;
}

bool FWFUNTest::testSerial(CleytinEngine *engine) {
    printf("\n[CLEYTIN TESTE SERIAL]\n");
    return true;
}

bool FWFUNTest::testSDCard(CleytinEngine *engine) {
    CleytinSdcard *sdcard = new CleytinSdcard();
    char **fileList = sdcard->list();
    delete sdcard;

    if(fileList == NULL) {
        return false;
    }

    uint i = 0;
    while(fileList[i] != NULL && i < MAX_FILE_LIST_SIZE) {
        free(fileList[i]);
        i++;
    }
    free(fileList);

    return true;
}

bool FWFUNTest::testButtons(CleytinEngine *engine) {
    this->testButton(engine, "CIMA", CLEYTIN_BTN_UP);
    this->testButton(engine, "DIREITA", CLEYTIN_BTN_RIGHT);
    this->testButton(engine, "BAIXO", CLEYTIN_BTN_DOWN);
    this->testButton(engine, "ESQUERDA", CLEYTIN_BTN_LEFT);
    this->testButton(engine, "A", CLEYTIN_BTN_A);
    this->testButton(engine, "B", CLEYTIN_BTN_B);
    this->testButton(engine, "C", CLEYTIN_BTN_C);
    this->testButton(engine, "START", CLEYTIN_BTN_START);
    return true;
}

void FWFUNTest::testButton(CleytinEngine *engine, const char *label, gpio_num_t btn) {
    CleytinControls *ctrl = new CleytinControls();
    CEContainer *container = new CEContainer();
    container->setPos(0, 0);
    container->setWidth(LCD_WIDTH_PIXELS);
    container->setHeight(LCD_HEIGHT_PIXELS);
    container->setPositioningStyle(CEPositioningStyle::FLEX_ROW);
    container->setAlignX(CEAlign::CENTER);
    container->setAlignY(CEAlign::CENTER);
    engine->addObject(container);

    this->putLabelInContainer(container, "Aperte ", 0);
    this->putLabelInContainer(container, label, 1, CLEYTIN_COLOR_PRIMARY);

    engine->loopAndRender();
    while(ctrl->waitClick() != btn);

    delete ctrl;
    engine->removeObject(container, true);
    engine->clear();
}

void FWFUNTest::showResults(CleytinEngine *engine, bool screen, bool serial, bool SDCard, bool buttons) {
    CleytinControls *ctrl = new CleytinControls();
    CEContainer *container = new CEContainer();

    container->setPos(20, 5);
    container->setWidth(LCD_WIDTH_PIXELS);
    container->setHeight(LCD_HEIGHT_PIXELS);
    container->setPositioningStyle(CEPositioningStyle::FLEX_COLUMN);
    container->setAlignX(CEAlign::START);
    container->setAlignY(CEAlign::START);
    engine->addObject(container);

    if(screen) {
        this->putLabelInContainer(container, "Tela   OK", 0, CLEYTIN_COLOR_SUCCESS);
    } else {
        this->putLabelInContainer(container, "Tela   ERRO", 0, CLEYTIN_COLOR_ERROR);
    }
    if(serial) {
        this->putLabelInContainer(container, "Serial OK", 1, CLEYTIN_COLOR_SUCCESS);
    } else {
        this->putLabelInContainer(container, "Serial ERRO", 1, CLEYTIN_COLOR_ERROR);
    }
    if(SDCard) {
        this->putLabelInContainer(container, "SDCard OK", 2, CLEYTIN_COLOR_SUCCESS);
    } else {
        this->putLabelInContainer(container, "SDCard ERRO", 2, CLEYTIN_COLOR_ERROR);
    }
    if(buttons) {
        this->putLabelInContainer(container, "Botões OK", 3, CLEYTIN_COLOR_SUCCESS);
    } else {
        this->putLabelInContainer(container, "Botões ERRO", 3, CLEYTIN_COLOR_ERROR);
    }

    engine->loopAndRender();
    ctrl->waitClick();
    engine->removeObject(container, true);
    delete ctrl;
    engine->clear();
    engine->loopAndRender();
}

void FWFUNTest::putLabelInContainer(CEContainer *container, const char *label, uint8_t pos, const CEColor color) {
    CEText *labelObj = new CEText();
    labelObj->setText(label);
    labelObj->setPriority(pos);
    labelObj->setSizeMultiplier(2);
    labelObj->setBaseColor(color);
    container->addObject(labelObj);
}

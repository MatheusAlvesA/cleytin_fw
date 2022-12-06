#include "fwfun_test.h"

void FWFUNTest::run(CleytinEngine *engine) {
    engine->clear();
    bool screen = this->testScreen(engine);
    engine->clear();
    bool serial = this->testSerial(engine);
    engine->clear();
    bool sdcard = this->testSDCard(engine);
    engine->clear();
    bool buttons = this->testButtons(engine);
    engine->clear();

    this->showResults(engine, screen, serial, sdcard, buttons);
}

bool FWFUNTest::testScreen(CleytinEngine *engine) {
    CERectangle *rect = new CERectangle();
    rect->setHeight(LCD_HEIGHT_PIXELS);
    rect->setFilled(true);
    rect->setPos(0, 0);
    engine->addObject(rect);
    for (unsigned int i = 0; i <= LCD_WIDTH_PIXELS; i++) {
        rect->setWidth(i);
        engine->render();
        cleytin_delay(5);
    }
    for (unsigned int i = 0; i <= LCD_WIDTH_PIXELS; i++) {
        rect->setPosX(i);
        engine->render();
        cleytin_delay(5);
    }
    engine->clear();
    delete rect;
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
    this->putLabelInContainer(container, label, 1);

    engine->render();
    while(ctrl->waitClick() != btn);

    delete container;
    delete ctrl;
    engine->clear();
}

void FWFUNTest::showResults(CleytinEngine *engine, bool screen, bool serial, bool SDCard, bool buttons) {
    CleytinControls *ctrl = new CleytinControls();
    CEContainer *container = new CEContainer();

    container->setPos(0, 0);
    container->setWidth(LCD_WIDTH_PIXELS);
    container->setHeight(LCD_HEIGHT_PIXELS);
    container->setPositioningStyle(CEPositioningStyle::FLEX_COLUMN);
    container->setAlignX(CEAlign::START);
    container->setAlignY(CEAlign::START);
    engine->addObject(container);

    if(screen) {
        this->putLabelInContainer(container, "Tela   OK", 0);
    } else {
        this->putLabelInContainer(container, "Tela   ERRO", 0);
    }
    if(serial) {
        this->putLabelInContainer(container, "Serial OK", 0);
    } else {
        this->putLabelInContainer(container, "Serial ERRO", 0);
    }
    if(SDCard) {
        this->putLabelInContainer(container, "SDCard OK", 0);
    } else {
        this->putLabelInContainer(container, "SDCard ERRO", 0);
    }
    if(buttons) {
        this->putLabelInContainer(container, "Botões OK", 0);
    } else {
        this->putLabelInContainer(container, "Botões ERRO", 0);
    }

    engine->render();
    ctrl->waitClick();
    delete container;
    delete ctrl;
    engine->clear();
}

void FWFUNTest::putLabelInContainer(CEContainer *container, const char *label, uint8_t pos) {
    CEText *labelObj = new CEText();
    labelObj->setText(label);
    labelObj->setPriority(pos);
    container->addObject(labelObj);
}

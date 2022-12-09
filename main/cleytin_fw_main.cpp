#include "cleytin_engine.h"
#include "ce_menu_helper.h"
#include "ce_container.h"
#include "ce_text.h"
#include "fwfun_sdcard.h"
#include "fwfun_startgame.h"
#include "fwfun_about.h"
#include "fwfun_test.h"
#include "cleytin_controls.h"

extern "C" {

void show_intro(CleytinEngine *engine);
void handle_options(CleytinEngine *engine, CEMenuHelper *menu);

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    CleytinControls::init();

    show_intro(engine);
    CEMenuHelper *menu = new CEMenuHelper();
    menu->setBaseColor({200, 0, 200});
    menu->setHighlightBGColor({200, 0, 200});
    menu->setTitle("Cleytin");

    menu->addOption("Iniciar Jogo", 1);
    menu->addOption("Micro SDCard", 2);
    menu->addOption("Diagnóstico", 3);
    menu->addOption("Sobre", 4);
    menu->addOption("Iniciar Jogo", 5);
    menu->addOption("Micro SDCard", 6);
    menu->addOption("Diagnóstico", 7);
    menu->addOption("Sobre", 8);
    menu->addOption("Iniciar Jogo", 9);
    menu->addOption("Micro SDCard", 10);
    menu->addOption("Diagnóstico", 11);
    menu->addOption("Sobre", 12);

    while(1) {
        handle_options(engine, menu);
        cleytin_delay(100);
    }

    delete menu;
    delete engine;
}

void handle_options(CleytinEngine *engine, CEMenuHelper *menu) {
    engine->addObject(menu);
    engine->render();
    while(!menu->handleControls()) {
        engine->render();
        cleytin_delay(10);
    }
    engine->clear();
    engine->render();
    switch (menu->getSelected()) {
        case 1: {
            FWFUNStartGame *fun = new FWFUNStartGame();
            fun->run(engine);
            delete fun;
        }
            break;
        case 2: {
            FWFUNSdcard *fun = new FWFUNSdcard();
            fun->run(engine);
            delete fun;
        }
            break;
        case 3: {
            FWFUNTest *fun = new FWFUNTest();
            fun->run(engine);
            delete fun;
        }
            break;
        case 4: {
            FWFUNAbout *fun = new FWFUNAbout();
            fun->run(engine);
            delete fun;
        }
            break;
    }
    engine->clear();
    menu->reset();
}

void show_intro(CleytinEngine *engine) {
    CEContainer *cont = new CEContainer();
    cont->setHeight(LCD_HEIGHT_PIXELS);
    cont->setWidth(LCD_WIDTH_PIXELS);
    cont->setPos(0, 0);
    cont->setPositioningStyle(FLEX_COLUMN);
    cont->setAlignX(CENTER);
    cont->setAlignY(CENTER);

    CEText *text = new CEText();
    text->setSizeMultiplier(4);
    text->setBaseColor({0, 91, 200});
    cont->addObject(text);

    engine->clear(true);
    engine->addObject(cont);

    cleytin_delay(200);
    text->setText("C      ");
    engine->render();
    cleytin_delay(200);
    text->setText("Cl     ");
    engine->render();
    cleytin_delay(200);
    text->setText("Cle    ");
    engine->render();
    cleytin_delay(200);
    text->setText("Cley   ");
    engine->render();
    cleytin_delay(200);
    text->setText("Cleyt  ");
    engine->render();
    cleytin_delay(200);
    text->setText("Cleyti ");
    engine->render();
    cleytin_delay(200);
    text->setText("Cleytin");
    engine->render();
    cleytin_delay(1000);

    engine->clear(true);
}

}

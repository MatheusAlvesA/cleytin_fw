#include "cleytin_engine.h"
#include "ce_menu_helper.h"
#include "ce_container.h"
#include "ce_text.h"
#include "cleytin_controls.h"
#include "cleytin_sdcard.h"

#define MAX_ROM_LIST_SIZE 200

extern "C" {

void show_intro(CleytinEngine *engine);

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();

    show_intro(engine);

    CEMenuHelper *menu = new CEMenuHelper();
    CleytinControls *controls = new CleytinControls();
    CleytinSdcard *sdcard = new CleytinSdcard();
    
    char **fileList = sdcard->list();
    if(fileList == NULL) {
        printf("Falha na leitura do cartão!\n");
        return;
    }

    uint i = 0;
    while(fileList[i] != NULL && i < 200) {
        printf("%s\n", fileList[i]);
        menu->addOption(fileList[i], i+1);
        free(fileList[i]);
        i++;
    }
    free(fileList);

    engine->addObject(menu);
    while(!menu->handleControls()) {
        engine->render();
        cleytin_delay(10);
    }
    uint idSelected = menu->getSelected();

    delete controls;
    delete menu;
    delete engine;
    delete sdcard;

    printf("Opcao selecionada: %d\n", idSelected);
}

void show_intro(CleytinEngine *engine) {
    CEContainer *cont = new CEContainer();
    cont->setHeight(64);
    cont->setWidth(128);
    cont->setPos(0, 0);
    cont->setPositioningStyle(FLEX_COLUMN);
    cont->setAlignX(CENTER);
    cont->setAlignY(CENTER);

    CEText *text = new CEText();
    cont->addObject(text);

    engine->clear(true);
    engine->addObject(cont);

    text->setText("       ");
    engine->render();
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

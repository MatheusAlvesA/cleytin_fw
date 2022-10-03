#include "cleytin_engine.h"
#include "ce_menu_helper.h"
#include "cleytin_controls.h"
#include "cleytin_sdcard.h"

#define MAX_ROM_LIST_SIZE 200

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();

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

}

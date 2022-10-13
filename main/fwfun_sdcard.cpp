#include "fwfun_sdcard.h"

void FWFUNSdcard::run(CleytinEngine *engine) {
    CEMenuHelper *menu = new CEMenuHelper();
    CleytinSdcard *sdcard = new CleytinSdcard();
    
    char **fileList = sdcard->list();
    if(fileList == NULL) {
        printf("Falha na leitura do cartão!\n");
        return;
    }

    uint i = 0;
    while(fileList[i] != NULL && i < 200) {
        menu->addOption(fileList[i], i+1);
        free(fileList[i]);
        i++;
    }
    free(fileList);

    engine->addObject(menu);
    engine->render();
    while(!menu->handleControls()) {
        engine->render();
        cleytin_delay(10);
    }
    uint idSelected = menu->getSelected();

    delete menu;
    delete sdcard;

    printf("Opcao selecionada: %d\n", idSelected);
}

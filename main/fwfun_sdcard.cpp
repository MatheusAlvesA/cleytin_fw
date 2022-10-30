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
    while(fileList[i] != NULL && i < MAX_FILE_LIST_SIZE) {
        if(sdcard->isRegularFile(fileList[i])) {
            menu->addOption(fileList[i], i+1);
        }
        i++;
    }

    engine->addObject(menu);
    engine->render();
    while(!menu->handleControls() && !menu->startPressed()) {
        engine->render();
        cleytin_delay(10);
    }
    uint idSelected = menu->getSelected();

    delete menu;

    if(idSelected == 0) {
        printf("Nenhum arquivo selecionado\n");
        delete sdcard;
        this->deleteFileList(fileList);
        return;
    }

    char *path = (char*) malloc(strlen(fileList[idSelected-1]) + 1);
    strcpy(path, fileList[idSelected-1]);
    this->deleteFileList(fileList);

    this->loadGame(engine, sdcard, path);
    free(path);
    delete sdcard;
}

void FWFUNSdcard::loadGame(CleytinEngine *engine, CleytinSdcard *sdcard, char *path) {
    engine->clear();
    sdcard->loadFileToFlash(path);
    printf("%u%%\n", sdcard->getLoadProgress());
    while(sdcard->getLoadProgress() < 100) {
        printf("%u%%\n", sdcard->getLoadProgress());
    }
    printf("%u%%\n", sdcard->getLoadProgress());
}

void FWFUNSdcard::deleteFileList(char **list) {
    uint i = 0;
    while(list[i] != NULL && i < MAX_FILE_LIST_SIZE) {
        free(list[i]);
        i++;
    }
    free(list[i]);
}

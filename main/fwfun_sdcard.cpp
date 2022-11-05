#include "fwfun_sdcard.h"

void FWFUNSdcard::run(CleytinEngine *engine) {
    CEMenuHelper *menu = new CEMenuHelper();
    CleytinSdcard *sdcard = new CleytinSdcard();
    
    char **fileList = sdcard->list();
    if(fileList == NULL) {
        this->showErrorScreen(engine);
        cleytin_delay(2000);
        delete menu;
        delete sdcard;
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

    CERectangle *barra = new CERectangle();
    barra->setPos(4, 30);
    barra->setHeight(4);
    barra->setWidth(120);
    barra->setFilled(false);

    CERectangle *progresso = new CERectangle();
    progresso->setPos(4, 30);
    progresso->setHeight(4);
    progresso->setWidth(0);
    progresso->setFilled(true);

    CEText *label = new CEText();
    label->setPos(12, 15);
    label->setText("Carregando...");

    engine->addObject(barra);
    engine->addObject(label);
    engine->addObject(progresso);

    if(!sdcard->loadFileToFlash(path)) {
        this->showErrorScreen(engine);
        delete barra;
        delete label;
        delete progresso;
        cleytin_unmount_fs();
        cleytin_delay(2000);
        return;
    }
    engine->render();
    while(sdcard->getLoadProgress() < 100) {
        progresso->setWidth((uint8_t) ((float)120 * ((float)sdcard->getLoadProgress() / (float)100)));
        engine->render();
    }
    progresso->setWidth(120);
    engine->render();
    cleytin_delay(200);
    engine->clear();

    delete barra;
    delete label;
    delete progresso;
}

void FWFUNSdcard::deleteFileList(char **list) {
    uint i = 0;
    while(list[i] != NULL && i < MAX_FILE_LIST_SIZE) {
        free(list[i]);
        i++;
    }
    free(list);
}

void FWFUNSdcard::showErrorScreen(CleytinEngine *engine) {
    engine->clear();
    CEText *errorLabel = new CEText();
    errorLabel->setPos(8, 15);
    errorLabel->setText("Erro no SDCard");
    engine->addObject(errorLabel);
    engine->render();
    engine->clear(true);
}

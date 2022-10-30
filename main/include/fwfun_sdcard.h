#ifndef FWFUN_SDCARD_H
#define FWFUN_SDCARD_H

#include "cleytin_engine.h"
#include "ce_menu_helper.h"
#include "cleytin_sdcard.h"

#define MAX_ROM_LIST_SIZE 200

class FWFUNSdcard {
public:
    void run(CleytinEngine *engine);

private:
    void loadGame(CleytinEngine *engine, CleytinSdcard *sdcard, char *path);
    void deleteFileList(char **list);
};

#endif

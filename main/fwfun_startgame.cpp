#include "fwfun_startgame.h"

void FWFUNStartGame::run(CleytinEngine *engine) {
    engine->clear();
    cleytin_reboot_and_start_game_rom();
}

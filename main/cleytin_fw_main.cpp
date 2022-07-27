#include "cleytin_engine.h"
#include "cleytin_storage.h"

#include "soc/rtc_wdt.h"

#define MAX_ROM_LIST_SIZE 200

extern "C" {

void app_main(void)
{
    CleytinEngine engine;
    CERectangle *rec = new CERectangle();
    rec->setPos(10, 10);
    rec->setWidth(30);
    rec->setHeight(10);
    rec->setFilled(true);
    rec->setPriority(2);

    CERectangle *rec2 = new CERectangle();
    rec2->setPos(5, 5);
    rec2->setWidth(60);
    rec2->setHeight(50);
    rec2->setFilled(false);


    engine.addObject(rec);
    engine.addObject(rec2);

    engine.render();

    uint16_t rot = 0;
    while(1) {
        rec->setRotation(rot);
        rot += 2;
        if(rot >= 360) {
            rot = 0;
        }
        engine.render();
        rtc_wdt_feed();
        cleytin_delay(1);
    }
    //while(1);

/*
    char **romList = list_valid_game_roms(MAX_ROM_LIST_SIZE);

    if(romList == NULL) {
        return;
    }

    uint32_t i = 0;
    char *firstRom = NULL;
    printf("Listando opções:\n");
    while(romList[i] != NULL) {
        if(firstRom == NULL) {
            firstRom = (char*) malloc(400);
            strncpy(firstRom, romList[i], 256);
        }
        printf("%s\n", romList[i]);
        i++;
    }

    i = 0;
    while(romList[i] != NULL) {
        free(romList[i]);
        i++;
    }
    free(romList);

    if(firstRom != NULL) {
        printf("Carregando rom...\n");
        strcat(firstRom, ".cleyrom");
        xTaskCreate(load_game_rom, "LOAD_ROM", 10*1024, firstRom, 1, NULL);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        while(cleytin_game_rom_load_progress < 100) {
            printf("Progresso: %d%%\n", cleytin_game_rom_load_progress);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        cleytin_reboot_and_load_game_rom();
    }
    printf("Não foi encontrada nenhuma game rom!\n");
*/
}

}

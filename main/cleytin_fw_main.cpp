#include "cleytin_engine.h"
/*
#include "cleytin_storage.h"

#define MAX_ROM_LIST_SIZE 200

void app_main(void)
{
    char **romList = list_valid_game_roms(MAX_ROM_LIST_SIZE);

    if(romList == NULL) {
        return;
    }

    uint32_t i = 0;
    char *firstRom = NULL;
    printf("Listando opções:\n");
    while(romList[i] != NULL) {
        if(firstRom == NULL) {
            firstRom = malloc(400);
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
}
*/

extern "C" void app_main(void)
{
    CleytinEngine engine;
}

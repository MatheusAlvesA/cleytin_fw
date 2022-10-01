#include "cleytin_engine.h"
#include "ce_menu_helper.h"
#include "cleytin_storage.h"
#include "cleytin_controls.h"

#define MAX_ROM_LIST_SIZE 200

extern "C" {

void app_main(void)
{
/*
    CleytinEngine *engine = new CleytinEngine();

    CEMenuHelper *menu = new CEMenuHelper();
    CleytinControls *controls = new CleytinControls();
    menu->addOption("Opção 01", 1);
    menu->addOption("Opção 02", 2);
    menu->addOption("Opção 03", 3);
    menu->addOption("Opção 04", 4);
    menu->addOption("Opção 05", 5);
    menu->addOption("Opção 06", 6);
    menu->addOption("Opção 07", 7);
    menu->addOption("Opção 08", 8);
    menu->addOption("Opção 09", 9);
    menu->addOption("Opção 10", 10);

    engine->addObject(menu);


    while(!menu->handleControls()) {
        engine->render();
        cleytin_delay(10);
    }
    uint idSelected = menu->getSelected();
    delete controls;
    delete menu;
    delete engine;

    printf("Opcao selecionada: %d\n", idSelected);
*/
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
}

}

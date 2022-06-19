#include <sys/stat.h>
#include <dirent.h> 
#include <sys/types.h>
#include <unistd.h>
#include <esp_ipc.h>
#include "cleytin_commons.h"

volatile uint8_t cleytin_game_rom_load_progress = 100;

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

char *extract_game_rom_file_name(char *name) {
    char path[400] = "/sdcard/";
    strcat(path, name);
    if(!is_regular_file(path)) {
        return NULL;
    }

    char *res = NULL;
    uint8_t i = 0;
    uint8_t j = 0;
    while(i < 255 && name[i] != '\0') {
        if(name[i] == '.') {
            j = i;
        }
        i++;
    }
    if(name[j] != '.') {
        return NULL;
    }

    char *temp = name + j + 1;
    if(strcmp(temp, "cleyrom") != 0) {
        return NULL;
    }

    i = 0;
    res = (char *)malloc(j+1);
    while(i < j) {
        res[i] = name[i];
        i++;
    }
    res[i] = '\0';

    return res;
}

void load_game_rom(void *path) {
    cleytin_load_rom_result_t res = cleytin_load_game_rom((char *)path);
    if(res != CLEYTIN_LOAD_ROM_RESULT_OK) {
        printf("Falha ao carregar (%d)\n", res);
        vTaskDelete(NULL);
    }
    printf("Rom carregada!\n");
    vTaskDelete(NULL);
}

void app_main(void)
{
    sdmmc_card_t *card = cleytin_mount_fs();
    if(card == NULL) {
        printf("Falha ao obter o sdcard\n");
        return;
    }

    TaskHandle_t xHandle = NULL;
    DIR *d;
    struct dirent *entry;
    d = opendir("/sdcard");
    while ((entry = readdir(d)) != NULL) {
        char *romName = extract_game_rom_file_name(entry->d_name);
        if(romName != NULL) {
            printf("%s\nCarregando rom...\n", romName);
            free(romName);
            xTaskCreate(load_game_rom, "LOAD", 10*1024, entry->d_name, 1, xHandle);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            while(cleytin_game_rom_load_progress < 100) {
                printf("Progresso: %d%%\n", cleytin_game_rom_load_progress);
                vTaskDelay(100 / portTICK_PERIOD_MS);
            }
            cleytin_reboot_and_load_game_rom();
        }
    }
    closedir(d);
    printf("Não foi encontrada nenhuma game rom!\n");
}

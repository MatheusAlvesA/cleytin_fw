#include "cleytin_storage.h"

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

char **list_valid_game_roms(size_t maxResults) {
    sdmmc_card_t *card = cleytin_mount_fs();
    if(card == NULL) {
        printf("Falha ao obter o sdcard\n");
        return NULL;
    }

    char **result = (char **)malloc(sizeof(char*) * maxResults);

    DIR *d;
    struct dirent *entry;
    d = opendir("/sdcard");
    size_t i = 0;
    while ((entry = readdir(d)) != NULL && i < maxResults) {
        char *romName = extract_game_rom_file_name(entry->d_name);
        if(romName != NULL) {
            result[i] = romName;
            i++;
        }
    }
    closedir(d);

    while(i < maxResults) {
        result[i] = NULL;
        i++;
    }

    return result;
}

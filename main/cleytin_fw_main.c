#include <string.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <sys/types.h>
#include <unistd.h>
#include "cleytin_commons.h"

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

void app_main(void)
{
    sdmmc_card_t *card = cleytin_mount_fs();
    if(card == NULL) {
        printf("Falha ao obter o sdcard\n");
        return;
    }

    DIR *d;
    struct dirent *entry;
    d = opendir("/sdcard");
    if (d) {
        while ((entry = readdir(d)) != NULL) {
            char *romName = extract_game_rom_file_name(entry->d_name);
            if(romName != NULL) {
                printf("%s\n", romName);
                free(romName);
            }
        }
        closedir(d);
    }
}

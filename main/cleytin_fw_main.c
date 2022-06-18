#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "cleytin_commons.h"

void app_main(void)
{
    cleytin_set_gpio_pin(2, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);

    sdmmc_card_t *card = cleytin_get_sdcard();
    if(card == NULL) {
        printf("Falha ao obter o sdcard\n");
        return;
    }

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

    // Use POSIX and C standard library functions to work with files:

    // First create a file.
    const char *file_hello = "/sdcard/hello.txt";

    printf("Abrindo arquivo %s\n", file_hello);
    FILE *f = fopen(file_hello, "w");
    if (f == NULL) {
        printf("Falha ao abrir o arquivo no modo escrita\n");
        return;
    }
    fprintf(f, "Hello %s!\n", card->cid.name);
    fclose(f);
    printf("Arquivo gravado\n");

    const char *file_foo = "/sdcard/foo.txt";

    // Check if destination file exists before renaming
    struct stat st;
    if (stat(file_foo, &st) == 0) {
        // Delete it if it exists
        unlink(file_foo);
    }

    // Rename original file
    printf("Renomeando o arquivo %s para %s\n", file_hello, file_foo);
    if (rename(file_hello, file_foo) != 0) {
        printf("Falha ao renomear\n");
        return;
    }

    // Open renamed file for reading
    printf("Lendo o arquivo %s\n", file_foo);
    f = fopen(file_foo, "r");
    if (f == NULL) {
        printf("Falha ao abrir o arquivo para leitura\n");
        return;
    }

    // Read a line from file
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);

    // Strip newline
    char *pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    printf("Lido do arquivo: '%s'\n", line);

    // All done, unmount partition and disable SDMMC peripheral
    esp_vfs_fat_sdcard_unmount("/sdcard", card);
    printf("Cartão desmontado\n");
}

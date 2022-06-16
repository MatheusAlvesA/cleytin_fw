#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cleytin_commons.h"

void app_main(void)
{
    printf("Olá mundo!\n");

    for (int i = 10; i >= 0; i--) {
        printf("Reiniciando em %d segundos...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    printf("Reiniciando agora.\n");
    fflush(stdout);
    reboot_and_load_game_rom();
}

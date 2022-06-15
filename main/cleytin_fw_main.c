#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spi_flash.h"
#include "esp_partition.h"

void app_main(void)
{
    printf("Olá mundo!\n");

    for (int i = 10; i >= 0; i--) {
        printf("Reiniciando em %d segundos...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    // Marcando flag para iniciar a rom
    const esp_partition_t* espPart = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "cleytin_flags");
    uint32_t buff[1] = {0xFFFFFFFF};
    esp_partition_erase_range(espPart, 0xFFFF - (4 * 1024) + 1, 4 * 1024);
    esp_err_t r = esp_partition_write(espPart, 0xFFFC, buff, 4);
    if(r == ESP_OK) {
        buff[0] = 0xFFFFFFFF;
        esp_partition_read(espPart, 0x0FFFC, buff, 4);
        printf("Flag gravada com sucesso %x = %x.\n", espPart->address + 0x0FFFC, buff[0]);
    }

    printf("Reiniciando agora.\n");
    fflush(stdout);
    esp_restart();
}

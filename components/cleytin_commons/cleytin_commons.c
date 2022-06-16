#include <stdio.h>
#include "cleytin_commons.h"
#include "esp_spi_flash.h"
#include "esp_partition.h"
#include "esp_system.h"

/**
 * @brief Reinicia o microcontrolador e marca a flag de game rom. Ao reiniciar o bootloader vai iniciar o jogo ao invés do firmware
 * 
 */
void reboot_and_load_game_rom(void)
{
    const esp_partition_t* espPart = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "cleytin_flags");
    uint32_t buff[1] = {0xFFFFFFFF};
    esp_partition_erase_range(espPart, CLEYTIN_GAME_ROM_ADDR - (4 * 1024), 4 * 1024);
    esp_partition_write(espPart, CLEYTIN_GAME_ROM_ADDR - sizeof(uint32_t), buff, sizeof(uint32_t));
    esp_restart();
}

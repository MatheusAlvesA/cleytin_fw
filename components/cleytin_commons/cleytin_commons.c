#include "cleytin_commons.h"

static const char *LOG_TAG = "cleytin";

void cleytin_reboot_and_load_game_rom(void)
{
    const esp_partition_t* espPart = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "cleytin_flags");
    uint32_t buff[1] = {0xFFFFFFFF};
    esp_partition_erase_range(espPart, CLEYTIN_GAME_ROM_ADDR - (4 * 1024), 4 * 1024);
    esp_partition_write(espPart, CLEYTIN_GAME_ROM_ADDR - sizeof(uint32_t), buff, sizeof(uint32_t));
    esp_restart();
}

esp_err_t cleytin_set_gpio_pin(gpio_num_t pin, cleytin_gpio_mode_t mode, gpio_int_type_t intr) {
    gpio_reset_pin(pin);
    gpio_config_t pinConf = {
        .pin_bit_mask = 1UL << pin,
        .mode = (CLEYTIN_GPIO_MODE_INPUT || CLEYTIN_GPIO_MODE_INPUT_PULLUP || CLEYTIN_GPIO_MODE_INPUT_PULLDOWN) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT,
        .pull_up_en = (CLEYTIN_GPIO_MODE_INPUT_PULLUP || CLEYTIN_GPIO_MODE_OUTPUT_PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = (CLEYTIN_GPIO_MODE_INPUT_PULLDOWN || CLEYTIN_GPIO_MODE_OUTPUT_PULLDOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE,
        .intr_type = intr,
    };
    return gpio_config(&pinConf);
}

sdmmc_card_t* cleytin_get_sdcard() {
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t *card;
    ESP_LOGI(LOG_TAG, "Inicializando SD Card");
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    slot_config.width = 1; // Modo de 1bit
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ESP_LOGI(LOG_TAG, "Montando sistema de arquivos");
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(LOG_TAG, "Falha ao montar o sistema de arquivos. Não foi possível formatar o SD Card");
        } else {
            ESP_LOGE(LOG_TAG, "Falha na comunicação com o SD Card (%s). ", esp_err_to_name(ret));
        }
        return NULL;
    }
    ESP_LOGI(LOG_TAG, "Sistema de arquivos montado");
    return card;
}

#include "cleytin_commons.h"

volatile uint8_t cleytin_game_rom_load_progress = 100;

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
        .mode = (mode == CLEYTIN_GPIO_MODE_INPUT || mode == CLEYTIN_GPIO_MODE_INPUT_PULLUP || mode == CLEYTIN_GPIO_MODE_INPUT_PULLDOWN) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT,
        .pull_up_en = (mode == CLEYTIN_GPIO_MODE_INPUT_PULLUP || mode == CLEYTIN_GPIO_MODE_OUTPUT_PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = (mode == CLEYTIN_GPIO_MODE_INPUT_PULLDOWN || mode == CLEYTIN_GPIO_MODE_OUTPUT_PULLDOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE,
        .intr_type = intr,
    };
    return gpio_config(&pinConf);
}

sdmmc_card_t* cleytin_mount_fs() {
    static sdmmc_card_t *card = NULL;
    if(card != NULL) {
        return card;
    }
    cleytin_set_gpio_pin((gpio_num_t)2, CLEYTIN_GPIO_MODE_INPUT_PULLUP, GPIO_INTR_DISABLE);
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    ESP_LOGI(LOG_TAG, "Inicializando SD Card");
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    slot_config.width = 1; // Modo de 1bit
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ESP_LOGI(LOG_TAG, "Montando sistema de arquivos");
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(LOG_TAG, "Falha ao montar o sistema de arquivos. N??o foi poss??vel formatar o SD Card");
        } else {
            ESP_LOGE(LOG_TAG, "Falha na comunica????o com o SD Card (%s). ", esp_err_to_name(ret));
        }
        return NULL;
    }
    ESP_LOGI(LOG_TAG, "Sistema de arquivos montado");
    return card;
}

cleytin_load_rom_result_t cleytin_load_game_rom(const char *path) {
    if(cleytin_mount_fs() == NULL) {
        return CLEYTIN_LOAD_ROM_RESULT_SDCARD_FAIL;
    }

    char fullPath[400] = "/sdcard/";
    strcat(fullPath, path);
    FILE *f = fopen(fullPath, "rb");
    if(f == NULL) {
        return CLEYTIN_LOAD_ROM_RESULT_INVALID_FILE;
    }

    const esp_partition_t* espPart = esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, "game_rom");
    unsigned char *buffer = (unsigned char *) malloc(CLEYTIN_BUFFER_SIZE);
    uint32_t i = 0;
    cleytin_game_rom_load_progress = 0;
    fseek(f, 0L, SEEK_END);
    float steps = ftell(f) / CLEYTIN_BUFFER_SIZE;
    rewind(f);
    while(i * CLEYTIN_BUFFER_SIZE < CLEYTIN_GAME_ROM_SIZE) {
        if(feof(f)) {
            break;
        }
        cleytin_game_rom_load_progress = (uint8_t)((i / steps) * 100);
        size_t readedSize = fread(buffer, 1, CLEYTIN_BUFFER_SIZE, f);
        esp_partition_erase_range(espPart, i * CLEYTIN_BUFFER_SIZE, CLEYTIN_BUFFER_SIZE);
        esp_partition_write(espPart, i * CLEYTIN_BUFFER_SIZE, buffer, readedSize);
        i++;
    }
    free(buffer);
    fclose(f);
    cleytin_game_rom_load_progress = 100;
    return CLEYTIN_LOAD_ROM_RESULT_OK;
}

void cleytin_delay(const uint64_t ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

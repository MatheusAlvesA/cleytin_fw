#include "driver/gpio.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "esp_spi_flash.h"
#include "esp_partition.h"
#include "esp_vfs_fat.h"

#define CLEYTIN_GAME_ROM_ADDR 0x10000
#define CLEYTIN_BOOT_FLAG_LOAD_GAME_ROM 0xFFFFFFFF

typedef enum {
    CLEYTIN_GPIO_MODE_INPUT = 0,
    CLEYTIN_GPIO_MODE_OUTPUT = 1,
    CLEYTIN_GPIO_MODE_INPUT_PULLUP = 2,
    CLEYTIN_GPIO_MODE_INPUT_PULLDOWN = 3,
    CLEYTIN_GPIO_MODE_OUTPUT_PULLUP = 4,
    CLEYTIN_GPIO_MODE_OUTPUT_PULLDOWN = 5,
} cleytin_gpio_mode_t;

/**
 * @brief Reinicia o microcontrolador e marca a flag de game rom. Ao reiniciar o bootloader vai iniciar o jogo ao invés do firmware
 * 
 */
void cleytin_reboot_and_load_game_rom(void);

/**
 * @brief Configura um dos pinos do ESP32
 * 
 * @param pin O pino a ser configurado
 * @param mode O modo para ser configurado no pino
 * @param intr Modo de interrupção do pino
 * @return esp_err_t 
 */
esp_err_t cleytin_set_gpio_pin(gpio_num_t pin, cleytin_gpio_mode_t mode, gpio_int_type_t intr);

/**
 * @brief Monta o sistema de arquivos em /sdcard e retorna o sd card padrão do Cleytin ou null em caso de falha
 * 
 * @return sdmmc_card_t* 
 */
sdmmc_card_t* cleytin_mount_fs();

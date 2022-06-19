#include <sys/stat.h>
#include <dirent.h> 
#include <sys/types.h>
#include <unistd.h>
#include <esp_ipc.h>
#include "cleytin_commons.h"

int is_regular_file(const char *path);

char *extract_game_rom_file_name(char *name);

void load_game_rom(void *path);

char **list_valid_game_roms(size_t maxResults);

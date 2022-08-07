#include "cleytin_engine.h"
#include "ce_rectangle.h"
#include "ce_bitmap.h"
#include "ce_text.h"
#include "cleytin_storage.h"

#define MAX_ROM_LIST_SIZE 200

extern "C" {

void app_main(void)
{
    CleytinEngine engine;
    CEText *txt = new CEText();
    txt->setText("XXXXX");
    txt->setPos(100, 20);
    txt->setPriority(2);

    CEBitmap *bmap = new CEBitmap();
    uint8_t *buff = (uint8_t *) malloc(2);
    buff[0] = 0b11111001;
    buff[1] = 0b10011111;
    bmap->setPos(10, 10);
    bmap->setWidth(4);
    bmap->setHeight(4);
    bmap->setBuffer(buff);

    CERectangle *rec2 = new CERectangle();
    rec2->setPos(5, 5);
    rec2->setWidth(60);
    rec2->setHeight(50);
    rec2->setFilled(false);


    engine.addObject(txt);
    engine.addObject(rec2);
    engine.addObject(bmap);

    engine.render();

    std::vector<size_t> *lista = engine.getCollisionsOn(0);
    printf("Encontrados: %d\n", lista->size());
    for (size_t i = 0; i < lista->size(); i++)
    {
        printf("Indice: %d\n", (*lista)[i]);
    }
    
    char *s = utf8ToLatin1("ÿ");
    printf("%s: \n", s);
    while(*s != '\0') {
        printf("%c %d\n", *s, *s);
        s++;
    }

/*
    uint16_t rot = 0;
    while(1) {
        rec->setRotation(rot);
        rot += 1;
        if(rot >= 360) {
            rot = 0;
        }
        engine.render();
        //cleytin_delay(2000);
    }
*/
/*
    char **romList = list_valid_game_roms(MAX_ROM_LIST_SIZE);

    if(romList == NULL) {
        return;
    }

    uint32_t i = 0;
    char *firstRom = NULL;
    printf("Listando opções:\n");
    while(romList[i] != NULL) {
        if(firstRom == NULL) {
            firstRom = (char*) malloc(400);
            strncpy(firstRom, romList[i], 256);
        }
        printf("%s\n", romList[i]);
        i++;
    }

    i = 0;
    while(romList[i] != NULL) {
        free(romList[i]);
        i++;
    }
    free(romList);

    if(firstRom != NULL) {
        printf("Carregando rom...\n");
        strcat(firstRom, ".cleyrom");
        xTaskCreate(load_game_rom, "LOAD_ROM", 10*1024, firstRom, 1, NULL);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        while(cleytin_game_rom_load_progress < 100) {
            printf("Progresso: %d%%\n", cleytin_game_rom_load_progress);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        cleytin_reboot_and_load_game_rom();
    }
    printf("Não foi encontrada nenhuma game rom!\n");
*/
}

}

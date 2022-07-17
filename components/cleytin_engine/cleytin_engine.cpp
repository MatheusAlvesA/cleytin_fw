#include "cleytin_engine.h"

CleytinEngine::CleytinEngine()
{
    this->buff = new uint8_t[(128 * 64) / 8]; // 128 por 64 bits de resolução
    memset(this->buff, 0, (128 * 64) / 8);
    this->api.init();
    this->api.renderBuffer(this->buff);
}

CleytinEngine::~CleytinEngine()
{
    delete this->buff;
}

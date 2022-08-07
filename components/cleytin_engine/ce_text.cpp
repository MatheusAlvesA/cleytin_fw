#include "ce_text.h"

CEText::CEText() {
    this->font = new CE8x12Font();
    this->text = (char *)malloc(1);
    this->text[0] = '\0';
    this->length = 0;
    this->wrap = true;
}

CEText::~CEText() {
    delete this->font;
    delete this->text;
}

void CEText::setCustomFont(CEFont *font) {
    delete this->font;
    this->font = font;
}

void CEText::setText(const char *buffer) {
    this->text = this->font->parseString(buffer);
    for (this->length = 0; *(buffer++) != '\0'; this->length++);
}

void CEText::setWrap(bool wrap) {
    this->wrap = wrap;
}

uint8_t CEText::getWidth() {
    if(this->posX + this->length * this->font->getCharWidth() >= LCD_WIDTH_PX) {
        return LCD_WIDTH_PX  - this->posX;
    } else {
        return this->length * this->font->getCharWidth();
    }
}

uint8_t CEText::getHeight() {
    if(!this->wrap) {
        return this->font->getCharHeight();
    }

    size_t width = this->length * this->font->getCharWidth();
    size_t availableWidth = LCD_WIDTH_PX - this->posX;
    if(width > availableWidth) {
        return ((width / availableWidth) + 1) * this->font->getCharHeight();
    } else {
        return this->font->getCharHeight();
    }
}

CERenderWindow* CEText::getRenderWindow() {
    CEPoint *start = new CEPoint((int) this->posX, (int) this->posY);
    CEPoint *end = new CEPoint((int) (this->posX + this->getWidth()), (int) (this->posY + this->getHeight()));
    CERenderWindow *window = new CERenderWindow(*start, *end);
    delete start;
    delete end;
    return window;
}

bool CEText::renderChar(uint8_t *buff, char c, uint8_t x, uint8_t y) {
    uint8_t *mappedPointer = this->font->getRawPonter() + this->font->getPositionOf(c);
    uint8_t charWidth = this->font->getCharWidth();
    uint8_t charHeight = this->font->getCharHeight();
    bool r = true;
    for (size_t cursorY = 0; cursorY < charHeight; cursorY++)
    {
        for (size_t cursorX = 0; cursorX < charWidth; cursorX++)
        {
            unsigned int bitPos = cursorX + (cursorY * charWidth);
            unsigned int bytePos = bitPos / 8;
            unsigned int bitOffset = bitPos % 8;
            if(!this->setPixel(
                buff,
                x + cursorX,
                y + cursorY,
                mappedPointer[bytePos] & (1 << (7 - bitOffset))
            )) {
                r = false;
            }
        }
    }
    return r;
}

bool CEText::renderToBuffer(uint8_t *buff, CERenderWindow *window) {
    CERenderWindow *w = this->getRenderWindow();
    uint8_t startX = w->topLeft->x;
    uint8_t cursorX = startX;
    uint8_t cursorY = w->topLeft->y;
    uint8_t maxX = w->bottomRight->x;
    uint8_t maxY = w->bottomRight->y;
    delete w;

    size_t charWidth = (size_t) this->font->getCharWidth();
    size_t charHeight = (size_t) this->font->getCharHeight();
    bool allRendered = true;
    for (size_t i = 0; this->text[i] != '\0'; i++)
    {
        if(!this->renderChar(buff, this->text[i], cursorX, cursorY)) {
            allRendered = false;
        }
        size_t nextCharXPos = ((size_t) cursorX) + charWidth; // Determine a posição do próximo char na linha

        if(nextCharXPos + charWidth <= maxX) { // Ainda cabe todo o próximo caractere nessa linha
            cursorX = (uint8_t) nextCharXPos; // Avance na linha
            continue; // Prossiga para renderizar o próximo char
        }
        // Não cabe todo o próximo char nessa linha
        if(!this->wrap) { // Se precisa renderizar tudo em uma linha
            if(nextCharXPos <= maxX) { // Se cabe ao menos uma parte
                cursorX = (uint8_t) nextCharXPos; // Avance na linha
                continue; // Prossiga para renderizar o próximo char
            }
            return false; // Não é mais possível renderizar nada na linha, terminando
        }
        // Realizando retorno de carrosel (Wrap)
        size_t nextCharYPos = ((size_t) cursorY) + charHeight; // Determine a posição y da próxima linha
        if(nextCharYPos > maxY) { // Se o início da próxima linha está fora do limite
            return false; // Termine o render
        }
        cursorY = (uint8_t) nextCharYPos; // Vá para a próxima linha
        cursorX = startX; // Comece do início da próxima linha
    }

    return allRendered;
}

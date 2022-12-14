#include "fwfun_about.h"

void FWFUNAbout::run(CleytinEngine *engine) {
    engine->clear();

    CleytinControls *ctrl = new CleytinControls();
    
    CEText *title = new CEText();
    title->setText("Cleytin");
    title->setPos(104, 80);
    title->setSizeMultiplier(2);

    CEText *ver = new CEText();
    ver->setText("0.2.0");
    ver->setPos(120, 110);
    ver->setSizeMultiplier(2);

    CEText *site = new CEText();
    site->setText("cleytin.com.br");
    site->setPos(48, 140);
    site->setSizeMultiplier(2);
    site->setBaseColor(CLEYTIN_COLOR_PRIMARY);

    engine->addObject(title);
    engine->addObject(ver);
    engine->addObject(site);

    engine->render();
    ctrl->waitClick();

    engine->clear();

    delete ctrl;
    delete title;
    delete ver;
    delete site;
}

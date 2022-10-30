#include "fwfun_about.h"

void FWFUNAbout::run(CleytinEngine *engine) {
    engine->clear();

    CleytinControls *ctrl = new CleytinControls();
    
    CEText *title = new CEText();
    title->setText("Cleytin");
    title->setPos(32, 0);
    CEText *ver = new CEText();
    ver->setText("0.1.0");
    ver->setPos(40, 16);
    CEText *site = new CEText();
    site->setText("cleytin.com.br");
    site->setPos(6, 48);

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

#include "coordinator_ssl.h"

Coordinator_SSL::Coordinator_SSL() {
    x = 0;
}

QString Coordinator_SSL::name() {
    return "Coordinator_SSL";
}

void Coordinator_SSL::configure() {
    addPlaybook(PLAYBOOK_DEFAULT, _playbook_default = new Playbook_Default());
    addPlaybook(PLAYBOOK_DEFAULT2, _playbook_default2 = new Playbook_Default());
}

void Coordinator_SSL::run() {
    if(x % 2)
        setPlaybook(PLAYBOOK_DEFAULT);
    else
        setPlaybook(PLAYBOOK_DEFAULT2);

    x++;
}

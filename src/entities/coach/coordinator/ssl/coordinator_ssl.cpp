#include "coordinator_ssl.h"

Coordinator_SSL::Coordinator_SSL() {
    timer.start();
    actualState = PLAYBOOK_DEFAULT;
}

QString Coordinator_SSL::name() {
    return "Coordinator_SSL";
}

void Coordinator_SSL::configure() {
    // Pb default => go to opposite goal and align
    addPlaybook(PLAYBOOK_DEFAULT, _playbook_default = new Playbook_Default());

    // Pb default2 => go to allie goal and align
    addPlaybook(PLAYBOOK_DEFAULT2, _playbook_default2 = new Playbook_Default2());
}

void Coordinator_SSL::run() {
    timer.stop();
    // Each 6 seconds, swap playbooks
    if(timer.getSeconds() >= 5.0) {
        timer.start();

        if(actualState == PLAYBOOK_DEFAULT) {
            actualState = PLAYBOOK_DEFAULT2;
        }
        else {
            actualState = PLAYBOOK_DEFAULT;
        }

        setPlaybook(actualState);
    }
}

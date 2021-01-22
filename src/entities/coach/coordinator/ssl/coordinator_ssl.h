#ifndef COORDINATOR_SSL_H
#define COORDINATOR_SSL_H

#include <src/entities/coach/coordinator/coordinator.h>

class Coordinator_SSL : public Coordinator
{
public:
    Coordinator_SSL();
    QString name();

private:
    // Coordinator inherited methods
    void configure();
    void run();

    // Playbook enums
    enum {
        PLAYBOOK_DEFAULT,
        PLAYBOOK_DEFAULT2
    };

    // Playbook pointers
    Playbook_Default *_playbook_default;
    Playbook_Default *_playbook_default2;

    int x;
};

#endif // COORDINATOR_SSL_H

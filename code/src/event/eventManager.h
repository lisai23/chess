#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "define.h"
#include "event.h"
#include <list>

class EventManager
{
public:
    static EventManager &instance(){static EventManager instance; return instance;}
    void init();
    uint32_t loop();
    void addEvent(event *e);

private:
    EventManager(/* args */);
    ~EventManager();

    std::list<event *> m_eventlist;
};

#define sEventManager EventManager::instance()
#endif //EVENTMANAGER_H

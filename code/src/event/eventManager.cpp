#include "eventManager.h"
#include "touchEvent.h"
#include <typeinfo>
#include <mutex>

std::mutex g_mutex;

EventManager::EventManager(/* args */)
{
}

EventManager::~EventManager()
{
    while (!m_eventlist.empty())
    {
        event *e = m_eventlist.back();
        if (nullptr != e)
        {
            e->distory();
        }
        
        m_eventlist.pop_back();
    }
}

void EventManager::init()
{

}

uint32_t EventManager::loop()
{
    while (true)
    {
        //std::cout << "m_eventlist.empty = " << m_eventlist.empty() << std::endl;
        g_mutex.lock();
        if (!m_eventlist.empty())
        {
            event *e = m_eventlist.back();
            if (nullptr != e)
            {
                e->handle();
                e->distory();
                // std::cout << "e type is " << typeid(*e).name() << std::endl;
                // std::cout << "touchevent type is " << typeid(TouchEvent).name() << std::endl;
            }
            else
            {
                std::cout << "e is null" << std::endl;
            }
            
            m_eventlist.pop_back();
        }    
        g_mutex.unlock();
        usleep(20000);
    }
    
    return 0;
}

void EventManager::addEvent(event *e)
{
    if (nullptr != e)
    {
        g_mutex.lock();
        m_eventlist.push_front(e);
        g_mutex.unlock();
    }
    else
    {
        std::cout << "addEvent e is null" << std::endl;
    }
}

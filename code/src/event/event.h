#ifndef EVENT_H
#define EVENT_H
#include "define.h"

class event
{
public:
    event(){}
    event(void *data, uint32_t size);
    ~event();
    event(const event &other);
    void operator=(const event &other);

    virtual void handle(){ std::cout << "handle in event" << std::endl; }
    virtual void update(void *data, uint32_t size);
    virtual void distory();
protected:
    void *m_data = nullptr;
    uint32_t m_size = 0;
};


#endif //EVENT_H

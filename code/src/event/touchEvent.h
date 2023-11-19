#ifndef TOUCHEVENT_H
#define TOUCHEVENT_H
#include "event.h"

class TouchEvent : public event
{
public:
    TouchEvent(){}
    TouchEvent(void *data, uint32_t size);
    ~TouchEvent();

    void handle() override;
private:
    /* data */
};


#endif //TOUCHEVENT_H

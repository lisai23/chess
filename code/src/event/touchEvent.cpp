#include "touchEvent.h"
#include "log.h"
#include "page.h"

TouchEvent::TouchEvent(void *data, uint32_t size)
    :event(data,size)
{
}

TouchEvent::~TouchEvent()
{
}

void TouchEvent::handle()
{   
    pos position;
    if (nullptr != m_data && m_size > 0)
    {
        memcpy(&position,m_data,m_size);
    }
    
    
    //std::cout << "file: " << __FILENAME__ << " touchscreen x: " << position.x << " y: " << position.y << std::endl;
    Debug_log("touchscreen x: %d, y: %d",position.x,position.y);
    //给到page
    page::touchEvent(position);
}

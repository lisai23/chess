#include "event.h"

event::event(void *data, uint32_t size)
    :m_size(size)
{
    if (size > 0)
    {
        m_data = malloc(size);
    }
    
    if (nullptr != data && nullptr != m_data)
    {
        memcpy(m_data,data,size);
    }
    else
    {
        m_size = 0;
    }
    
}

event::~event()
{
    if (nullptr != m_data)
    {
        std::cout << "free data" << std::endl;
        free(m_data);
        m_data = nullptr;  
    }
    std::cout << "~event" << std::endl;
    m_size = 0;
}

event::event(const event &other)
{
    m_size = other.m_size;
    if (other.m_size > 0 && nullptr != other.m_data)
    {
        m_data = malloc(other.m_size);
        if (nullptr != m_data)
        {
            memcpy(m_data,other.m_data,other.m_size);
        }
    }
}

void event::operator=(const event &other)
{
    m_size = other.m_size;
    if (other.m_size > 0 && nullptr != other.m_data)
    {
        m_data = malloc(other.m_size);
        if (nullptr != m_data)
        {
            memcpy(m_data,other.m_data,other.m_size);
        }
    }
}

void event::update(void *data, uint32_t size)
{
    if (nullptr != m_data)
    {
        free(m_data);
        m_data = nullptr;
    }
    
    m_size = size;
    if (size > 0)
    {
        m_data = malloc(size);
    }
    
    if (nullptr != data && nullptr != m_data)
    {
        memcpy(m_data,data,size);
    }
    else
    {
        m_size = 0;
    }
}

void event::distory()
{
    if (nullptr != m_data && m_size > 0)
    {
        free(m_data);
        m_data = nullptr;
        m_size = 0;
    }   
}

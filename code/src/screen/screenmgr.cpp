#include "screenmgr.h"
#include <sys/mman.h>
#include<fcntl.h>
#include <unistd.h>

ScreenMgr::ScreenMgr(/* args */)
{
}

ScreenMgr::~ScreenMgr()
{
    if (m_init)
    {
        close(m_screenfd);
        if (nullptr != m_basescreen)
        {
            munmap(m_basescreen,800*480*4);
        }
    }

    for (size_t i = 0; i < m_mapPage.size(); i++)
    {
        if (nullptr != m_mapPage[i].backup)
        {
            delete m_mapPage[i].backup;
            m_mapPage[i].backup = nullptr;
            std::cout << "【" << __FILE__ << "】 line: " << __LINE__ << std::endl;
        }
    }
}

void ScreenMgr::init()
{
    m_init = true;
    m_screenfd=open("/dev/fb0",O_RDWR);
    m_basescreen = (uint32_t *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,m_screenfd,0);
}

void ScreenMgr::openPage(uint32_t pageid, pos position, uint32_t width, uint32_t height, uint32_t *data)
{
    if (nullptr == m_basescreen)
    {
        std::cout << "screen not init." << std::endl;
        return;
    }

    if (position.x + height > SCREENWIDTH || position.y + width > SCREENHEIGHT)
    {
        std::cout << "x = " << position.x << ", w = " << width << std::endl;
        std::cout << "y = " << position.y << ", h = " << height << std::endl;
        std::cout << "position is out-of-bounds." << std::endl;
        return;
    }
    
    pageInfo info;
    info.id = pageid;
    info.position = position;
    info.width = width;
    info.height = height;

    if (m_mapPage.count(pageid) > 0)
    {
        if (E_Displaying == m_mapPage[pageid].state)
        {
            std::cout << "page " << pageid << " is already displaying." << std::endl;
            return;
        }
    }
    else
    {
        m_mapPage[pageid] = info;
        m_mapPage[pageid].backup = new uint32_t[width*height];
    }
    
    

    uint32_t *p = m_mapPage[pageid].backup;
    uint32_t tmp = 0;
    for (uint32_t h = position.x; h < position.x+height; h++)
    {
        for (uint32_t w = position.y; w < position.y+width; w++)
        {
            p[tmp++] = m_basescreen[w*800+799-h];
        }
    }
    
    tmp = 0;
    for (uint32_t h = position.x; h < position.x+height; h++)
    {
        for (uint32_t w = position.y; w < position.y+width; w++)
        {
            m_basescreen[w*800+799-h] = data[tmp++];
        }
    }

    m_mapPage[pageid].state = E_Displaying;
}

void ScreenMgr::closePage(uint32_t pageid)
{
    if (nullptr == m_basescreen)
    {
        std::cout << "screen not init." << std::endl;
        return;
    }

    if (m_mapPage.count(pageid) > 0)
    {
        if (E_NotDisplay == m_mapPage[pageid].state)
        {
            std::cout << "page " << pageid << " is already closed." << std::endl;
            return;
        }
    }
    else
    {
        std::cout << "there is no page id: " << pageid << std::endl;
        return;
    }

    pageInfo info = m_mapPage[pageid];
    uint32_t *p = m_mapPage[pageid].backup;
    uint32_t tmp = 0;

    std::cout << "width: " << info.width << std::endl;
    std::cout << "height: " << info.height << std::endl;
    std::cout << "x: " << info.position.x << std::endl;
    std::cout << "y: " << info.position.y << std::endl;
    for (uint32_t h = info.position.x; h < info.position.x+info.height; h++)
    {
        for (uint32_t w = info.position.y; w < info.position.y+info.width; w++)
        {
            m_basescreen[w*800+799-h] = p[tmp++];
        }
    }

    m_mapPage[pageid].state = E_NotDisplay;
}

uint32_t ScreenMgr::getNewPageID()
{
    uint32_t pageid = 0;
    for (uint32_t id = 1; id < MAXPAGEID; id++)
    {
        if (m_mapPage.count(id) == 0)
        {
            pageid = id;
            break;
        }
    }
    
    return pageid;
}

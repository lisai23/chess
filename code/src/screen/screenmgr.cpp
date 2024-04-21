#include "screenmgr.h"
#include<fcntl.h>
#include <unistd.h>
#include "eventManager.h"
#include "touchEvent.h"
#include "log.h"
#include "Timer.h"
#ifdef LINUX_ARM
#include <sys/mman.h>
#endif

ScreenMgr::ScreenMgr(/* args */)
{
}

ScreenMgr::~ScreenMgr()
{
    recover();

    for (size_t i = 0; i < m_mapPage.size(); i++)
    {
        if (nullptr != m_mapPage[i].backup)
        {
            delete m_mapPage[i].backup;
            m_mapPage[i].backup = nullptr;
        }
    }

    if (m_init)
    {
        close(m_screenfd);
        if (nullptr != m_basescreen)
        {
#ifdef LINUX_ARM
            munmap(m_basescreen,800*480*4);
#endif
        }
    }
}

void ScreenMgr::backPack()
{
    Debug_log("backPack screen");
}

void ScreenMgr::recover()
{
    Debug_log("recover screen");
}

void ScreenMgr::testfunc()
{
    Debug_log("test timer trigger");
}

void ScreenMgr::init()
{
    backPack();
    m_init = true;
    m_screenfd=open("/dev/fb0",O_RDWR);
#ifdef LINUX_ARM
    m_basescreen = (uint32_t *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,m_screenfd,0);
#endif

    //打开触摸屏
    m_screenfd=open("/dev/input/event0",O_RDWR);
	if(m_screenfd < 0)
	{
		perror("open chumuping fail:");
	}
    else
    {
#ifdef LINUX_ARM
        m_thread = std::thread(&ScreenMgr::touchThread,this);
        m_thread.detach();
#endif
    }

    // static Timer test;
    // test.connect(std::bind(&ScreenMgr::testfunc,this));
    // test.start(2000);
    // Debug_log("test timer is start");
    // usleep(5000000);
    // test.reStart(1000,true);
}

void ScreenMgr::openPage(Image *img)
{
    if (nullptr == m_basescreen)
    {
        std::cout << "screen not init." << std::endl;
        return;
    }

    if (nullptr == img)
    {
        Debug_log("img is null !");
        return;
    }
    
    pos position = img->getPosition();
    uint32_t width = img->getWidth();
    uint32_t height = img->getHeight();
    uint32_t *data = img->getDataPointer();

    if (nullptr == data)
    {
        Debug_log("img data is null !");
        return;
    }
    
    uint32_t pageid = getNewPageID();
    img->setPageID(pageid);

    if (position.x + height > SCREEN_WIDTH || position.y + width > SCREEN_HEIGHT)
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
        //std::cout << "screen not init." << std::endl;
        Debug_log("screen not init.");
        return;
    }

    if (m_mapPage.count(pageid) > 0)
    {
        if (E_NotDisplay == m_mapPage[pageid].state)
        {
            //std::cout << "page " << pageid << " is already closed." << std::endl;
            Debug_log("page %d is already closed.", pageid);
            return;
        }
    }
    else
    {
        //std::cout << "there is no page id: " << pageid << std::endl;
        Debug_log("there is no page id: %d",pageid);
        return;
    }

    pageInfo info = m_mapPage[pageid];
    uint32_t *p = m_mapPage[pageid].backup;
    uint32_t tmp = 0;

    // std::cout << "width: " << info.width << std::endl;
    // std::cout << "height: " << info.height << std::endl;
    // std::cout << "x: " << info.position.x << std::endl;
    // std::cout << "y: " << info.position.y << std::endl;
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

void ScreenMgr::touchThread()
{
#ifdef LINUX_ARM
    struct input_event xy;
    pos position;
    TouchEvent e;
    while (true)
    {
        bool updata = false;
        position.clean();
        //防抖
        usleep(80000);
        //读取触摸屏数据
        read(m_screenfd,&xy,sizeof(xy));
        if(xy.type == EV_ABS)  //如果事件类型为触摸屏
        {   
            if (xy.code == ABS_X )//获取x轴坐标
            {
                position.x = xy.value;
                updata = true;
            }
        }

        read(m_screenfd,&xy,sizeof(xy));
        if(xy.type == EV_ABS)  //如果事件类型为触摸屏
        {   
            if (xy.code == ABS_Y )//获取x轴坐标
            {
                position.y = xy.value;
                updata = true;
            }
        }

        if (updata)
        {
            Debug_log("touchThread: x = %d, y = %d",position.x,position.y);
            position.type = SCREEN_POS;
            e.update(&position,sizeof(position));
            sEventManager.addEvent(&e);
        }
        
        
        //sleep(2);
    }
#endif
}

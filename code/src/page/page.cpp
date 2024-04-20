#include "page.h"
#include "log.h"

std::map<pos, std::stack<page *>> page::s_PageMap = {};

page::page(/* args */)
{
    m_pos.clean();
    m_rect.clean();
}

page::~page()
{
}

void page::initPageMap()
{
    pos point;
    for (size_t y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (size_t x = 0; x < SCREEN_WIDTH; x++)
        {
            point.x = x;
            point.y = y;

            s_PageMap[point] = std::stack<page *>();
        }
    }
    Debug_log("s_PageMap size:%d",s_PageMap.size());
}

void page::setRect(rect re)
{
    m_rect = re;
}

void page::setRect(int32_t width, int32_t height)
{
    m_rect.width = width;
    m_rect.height = height;
}

rect page::getRect()
{
    return m_rect;
}

void page::open()
{
    if (m_rect.width == 0 || m_rect.height == 0)
    {
        Debug_log("the size of page is 0");
        return;
    }

    registPageEvent();
    
}

void page::close()
{

}

void page::registPageEvent()
{
    pos point;
    for (size_t y = m_pos.y; y < m_pos.y+m_rect.height; y++)
    {
        for (size_t x = m_pos.x; x < m_pos.x+m_rect.width; x++)
        {
            point.x = x;
            point.y = y;

            s_PageMap[point].push(this);
        }
    }
}

void page::touchEvent(pos touch)
{
    if (s_PageMap.count(touch) > 0)
    {
        if (false == s_PageMap[touch].empty())
        {
            page *p_page = s_PageMap[touch].top();
            if (nullptr != p_page)
            {
                p_page->onClick();
            }
            else
            {
                Debug_log("the page on pos: %d,%d is nullptr",touch.x,touch.y);
            }
        }
        else
        {
            Debug_log("there is on page display on pos: %d,%d",touch.x,touch.y);
        }
    }
    else
    {
        Debug_log("the point is not regist: %d,%d, size:%d",touch.x,touch.y,s_PageMap.size());
    }
}

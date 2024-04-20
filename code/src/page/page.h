#ifndef PAGE_H
#define PAGE_H
#include <map>
#include <stack>
#include <memory>
#include "define.h"
#include "image.h"

class page
{
public:
    page(/* args */);
    ~page();
    static void initPageMap();

    virtual void setRect(rect re);
    virtual void setRect(int32_t width, int32_t height);
    virtual rect getRect();

    virtual void onClick() = 0;
    static void touchEvent(pos touch);
protected:
    virtual void open();
    virtual void close();
private:
    static std::map<pos, std::stack<page *>> s_PageMap;
    void registPageEvent();

    pos m_pos;
    rect m_rect;
    Image m_image;
};


#endif //PAGE_H
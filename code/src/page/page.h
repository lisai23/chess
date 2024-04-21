#ifndef PAGE_H
#define PAGE_H
#include <map>
#include <stack>
#include <memory>
#include "define.h"
#include "image.h"
//#include "stack.h"

class page
{
public:
    page(/* args */);
    ~page();
    static void initPageMap();

    virtual void setRect(rect re);
    virtual void setRect(int32_t width, int32_t height);
    virtual rect getRect();

    virtual void onClick(pos position) = 0;
    static void touchEvent(pos touch);

    void setPos(pos position){ m_pos = position; }
    pos getPos(){ return m_pos; }
protected:
    void open();
    void close();
    void flash(bool state);

    pos m_pos;
    rect m_rect;
private:
    static std::map<pos, std::stack<page *>> s_PageMap;
    void registPageEvent();
    void unRegistPageEvent();

    
    Image *m_image;
    Image *m_backUp;
};


#endif //PAGE_H
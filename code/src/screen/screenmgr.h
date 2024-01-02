#ifndef SCREENMGR_H
#define SCREENMGR_H
#include "define.h"
#include "image.h"
#include <map>
#include <thread>

#define SCREENWIDTH 800
#define SCREENHEIGHT 480
#define MAXPAGEID 1000

struct pageInfo
{
    uint32_t id;
    pos position;
    uint32_t width;
    uint32_t height;
    uint32_t state;
    uint32_t *backup;
    pageInfo()
    {
        id = 0;
        position.x = 0;
        position.y = 0;
        width = 0;
        height = 0;
        state = E_NotDisplay;
        backup = nullptr;
    }
};


class ScreenMgr
{
public:
    static ScreenMgr &instance(){static ScreenMgr instance; return instance;}
    void testfunc();
    void init();
    void openPage(Image *img);
    void closePage(uint32_t pageid);
    uint32_t getNewPageID();

    void touchThread();
private:
    ScreenMgr(/* args */);
    ~ScreenMgr();
    void recover();
    void backPack();

    bool m_init = false;
    int32_t m_screenfd = 0;
    uint32_t *m_basescreen = nullptr;
    std::map<uint32_t,pageInfo> m_mapPage;
    std::thread m_thread;
};

#define sScreenMgr ScreenMgr::instance()

#endif //SCREENMGR_H
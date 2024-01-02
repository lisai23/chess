#include "define.h"
#include "image/image.h"
#include "screenmgr.h"
#include "touchEvent.h"
#include "eventManager.h"
#include <ctime>
#ifdef LINUX_ARM
#include<unistd.h>
#include<signal.h>
#endif
#include "log.h"
#include "Timer.h"

typedef void (*sighandler)(int);

void cleanup(int)
{
    Debug_log("cleanup");
    
    exit(0);
}



int main(int argc, char const *argv[])
{
    signal(SIGINT,cleanup);
    log_init();
    sTimerManager.init();
    sScreenMgr.init();
    Image img("./resource/chessboard.bmp");
    img.setFlash(true);
    //img.show();
    sleep(5);
    img.setFlash(false);

    return sEventManager.loop();
}
#include "define.h"
#include "image/image.h"
#include "screenmgr.h"
#include "touchEvent.h"
#include "eventManager.h"
#include <ctime>
#include "log.h"
#include "Timer.h"

int main(int argc, char const *argv[])
{
    log_init();
    sTimerManager.init();
    sScreenMgr.init();

    
    
    return sEventManager.loop();
}
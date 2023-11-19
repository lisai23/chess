#include "define.h"
#include "image/image.h"
#include "screenmgr.h"
#include "touchEvent.h"
#include "eventManager.h"
#include <ctime>
#include "log.h"


int main(int argc, char const *argv[])
{
    log_init();
    sScreenMgr.init();
    // Image img("./resource/chessboard.bmp");
    
    // pos position;
    // position.x = 0;
    // position.y = 100;
    // img.show(position);
    // sleep(2);
    // img.close();

    // TouchEvent e(&position,sizeof(position));
    // sEventManager.addEvent(&e);
    
    return sEventManager.loop();
}
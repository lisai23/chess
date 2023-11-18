#include "define.h"
#include "image/image.h"
#include "screenmgr.h"

int main(int argc, char const *argv[])
{
    sScreenMgr.init();
    Image img("./resource/chessboard_back.bmp");
    
    pos position;
    position.x = 50;
    position.y = 100;
    img.show(position);
    sleep(2);
    img.close();
    
    return 0;
}
#ifndef HANDLEIF_H
#define HANDLEIF_H
#include <string>
#include "define.h"
#include "image.h"

class HandleIf
{
private:
    /* data */
public:
    HandleIf(/* args */);
    ~HandleIf();

    virtual void LoadImage(std::string path, Image *img) = 0;
};


#endif //HANDLEIF_H
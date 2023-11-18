#ifndef PNGHANDLE_H
#define PNGHANDLE_H
#include "handleIf.h"
#include <string>

class PNGHandle : public HandleIf
{
public:
    PNGHandle(/* args */);
    ~PNGHandle();

    void LoadImage(std::string path, Image *img) override;
};


#endif //PNGHANDLE_H
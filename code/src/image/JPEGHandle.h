#ifndef JPEGHANDLE_H
#define JPEGHANDLE_H
#include "handleIf.h"
#include <string>

class JPEGHandle : public HandleIf
{
public:
    JPEGHandle(/* args */);
    ~JPEGHandle();

    void LoadImage(std::string path, Image *img) override;
};


#endif //JPEGHANDLE_H
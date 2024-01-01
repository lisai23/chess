#ifndef IMAGEHANDLE_H
#define IMAGEHANDLE_H
#include "define.h"
#include "handleIf.h"
#include "image.h"

class ImageHandle
{
public:
    ImageHandle(/* args */);
    ~ImageHandle();

    static void SetImageType(uint32_t imagetype, Image *img);
    static void LoadImage(std::string path, Image *img);
private:
    static HandleIf *handle;
};


#endif //IMAGEHANDLE_H
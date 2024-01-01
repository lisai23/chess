#include "imageHandle.h"
#include "BMPHandle.h"
#include "JPEGHandle.h"
#include "PNGHandle.h"

HandleIf *ImageHandle::handle = nullptr;

ImageHandle::ImageHandle(/* args */)
{
    handle = nullptr;
}

ImageHandle::~ImageHandle()
{
    if (handle)
    {
        delete handle;
    }
}

void ImageHandle::SetImageType(uint32_t imagetype, Image *img)
{
    std::cout << "image type is ";
    switch (imagetype)
    {
        case BITMAP_TYPE:
            img->setType(BITMAP_TYPE);
            if (handle)
            {
                delete handle;
            }
            handle = new BMPHandle();
            std::cout << "BMP." << std::endl;
            break;
        case JPEG_TYPE:
            img->setType(JPEG_TYPE);
            if (handle)
            {
                delete handle;
            }
            handle = new JPEGHandle();
            std::cout << "JPEG." << std::endl;
            break;
        case PNG_TYPE:
            img->setType(PNG_TYPE);
            if (handle)
            {
                delete handle;
            }
            handle = new PNGHandle();
            std::cout << "PNG." << std::endl;
            break;
        default:
            std::cout << "Unknow type " << imagetype << "." << std::endl;
            break;
    }
}

void ImageHandle::LoadImage(std::string path, Image *img)
{
    if (handle)
    {
        handle->LoadImage(path, img);
        delete handle;
    }
}
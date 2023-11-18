#ifndef BMPHANDLE_H
#define BMPHANDLE_H
#include "handleIf.h"
#include <string>

class BMPHandle : public HandleIf
{
public:
    BMPHandle(/* args */);
    ~BMPHandle();

    void LoadImage(std::string path, Image *img) override;
};


#endif //BMPHANDLE_H
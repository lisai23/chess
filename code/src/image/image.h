#ifndef IMAGE_H
#define IMAGE_H
#include "define.h"
#include <string>

class Image
{
public:
    Image();
    Image(std::string path);
    ~Image();

    void loadFile(std::string path);
    ImageType getImageType(){return m_type;}

    void show(pos p);
    void close();

    void setType(ImageType type);
    ImageType getType();

    void setWidth(uint32_t width);
    uint32_t getWidth();

    void setHeight(uint32_t height);
    uint32_t getHeight();

    void setSize(uint32_t size);
    uint32_t getSize();

    void setDataPointer(uint32_t *pdata);
    uint32_t *getDataPointer(); 
    
private:
    std::string m_filepath;
    uint32_t *m_data = nullptr;
    uint32_t m_size = 0U;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    ImageType m_type = UNKNOWN_TYPE; 
    DisplayState m_displaystate = E_NotDisplay;
    uint32_t m_pageid;
};


#endif //IMAGE_H
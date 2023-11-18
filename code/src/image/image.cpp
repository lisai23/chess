#include "image.h"
#include "imageHandle.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "screenmgr.h"

Image::Image(/* args */)
{
    m_filepath.clear();
}

Image::Image(std::string path)
{
    if (nullptr == path.c_str())
    {
        std::cout << "file pointer is null !" << std::endl;
        return;
    }

    struct stat st; 
    int32_t ret = stat(path.c_str(), &st);
    if (ret) 
    {
        std::cout << "file " << path.c_str() << " is null !" << std::endl;
        return; 
    }
    
    loadFile(path);
}

Image::~Image()
{
    if (m_data)
    {
        delete m_data;
        m_data = nullptr;
    }    
}

void Image::loadFile(std::string path)
{
    if (nullptr == path.c_str())
    {
        std::cout << "file pointer is null !" << std::endl;
        return;
    }

    struct stat st; 
    int32_t ret = stat(path.c_str(), &st);
    if (ret) 
    {
        std::cout << "file " << path.c_str() << " is null !" << std::endl;
        return; 
    }

    m_filepath = path;
    FILE *pFile=fopen(path.c_str(),"rb");
    if (pFile==NULL)
    {
        std::cout << "Open file: " << path.c_str() << " error !" << std::endl;
        return;
    }

    int32_t type;
    fread(&type,4,1,pFile);
    type = BITMAP_TYPE;

    ImageHandle::SetImageType(type,this);
    ImageHandle::LoadImage(path,this);

    fclose(pFile);
    
}

void Image::show(pos p)
{
    if (nullptr != m_data)
    {
        /*换方向*/
        pos tmp;
        tmp.x = p.y;
        tmp.y = p.x;

        m_pageid = sScreenMgr.getNewPageID();
        sScreenMgr.openPage(m_pageid,tmp,m_width,m_height,m_data);

        m_displaystate = E_Displaying;
    }
    else
    {
        std::cout << "image data is null" << std::endl;
    }
}

void Image::close()
{
    if (E_Displaying == m_displaystate)
    {
        sScreenMgr.closePage(m_pageid);
        m_displaystate = E_NotDisplay;
    }
    
}

void Image::setType(ImageType type)
{
    m_type = type;
}

ImageType Image::getType()
{
    return m_type;
}

void Image::setWidth(uint32_t width)
{
    m_width = width;
}

uint32_t Image::getWidth()
{
    return m_width;
}

void Image::setHeight(uint32_t height)
{
    m_height = height;
}

uint32_t Image::getHeight()
{
    return m_height;
}

void Image::setSize(uint32_t size)
{
    m_size = size;
}

uint32_t Image::getSize()
{
    return m_size;
}

void Image::setDataPointer(uint32_t *pdata)
{
    m_data = pdata;
}

uint32_t *Image::getDataPointer()
{
    return m_data;
}

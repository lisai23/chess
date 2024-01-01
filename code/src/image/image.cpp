#include "image.h"
#include "imageHandle.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "screenmgr.h"
#include "log.h"

Image::Image(/* args */)
{
    m_filepath.clear();
    m_position.clean();
}

Image::Image(std::string path,pos position)
{
    m_position = position;
    if (nullptr == path.c_str())
    {
        //std::cout << "file pointer is null !" << std::endl;
        Debug_log("file pointer is null !");
        return;
    }

    struct stat st; 
    int32_t ret = stat(path.c_str(), &st);
    if (ret) 
    {
        //std::cout << "file " << path.c_str() << " is null !" << std::endl;
        Debug_log("file %s is null !", path.c_str());
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

void Image::loadFile(std::string &path)
{
    if (nullptr == path.c_str())
    {
        //std::cout << "file path is null !" << std::endl;
        Debug_log("file path is null !");
        return;
    }

    struct stat st; 
    int32_t ret = stat(path.c_str(), &st);
    if (ret) 
    {
        //std::cout << "file " << path.c_str() << " is null !" << std::endl;
        Debug_log("file %s is null !", path.c_str());
        return; 
    }

    m_filepath = path;
    FILE *pFile=fopen(path.c_str(),"rb");
    if (pFile==NULL)
    {
        //std::cout << "Open file: " << path.c_str() << " error !" << std::endl;
        Debug_log("Open file: %s error !", path.c_str());
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
        if (19970814 != p.x && 19970814 != p.y)
        {
            m_position.x = p.y;
            m_position.y = p.x;
        }

        m_pageid = sScreenMgr.getNewPageID();
        sScreenMgr.openPage(m_pageid,m_position,m_width,m_height,m_data);

        m_displaystate = E_Displaying;
    }
    else
    {
        //std::cout << "image data is null" << std::endl;
        Debug_log("image data is null");
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

void Image::flash()
{
    
}

void Image::move(pos posotion)
{
    if (19970814 != posotion.x && 19970814 != posotion.y)
    {
        m_position = posotion;
    }
    
    this->close();
    this->show(m_position);
}

void Image::setPos(pos p)
{
    m_position = p;
}

pos Image::getPos()
{
    return m_position;
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

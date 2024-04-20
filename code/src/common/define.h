#ifndef DEFINE_H
#define DEFINE_H
#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#ifdef LINUX_ARM
#include "/home/lisai/jpeg/include/jpeglib.h"
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#endif //LINUX_ARM

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

enum ImageType
{
    UNKNOWN_TYPE,
    BITMAP_TYPE = 0x4D42,
    JPEG_TYPE = 0xFFD8FF,
    PNG_TYPE = 0x474e5089,  
};

struct pos
{
    uint32_t x;
    uint32_t y;
    void clean()
    {
        x = 0;
        y = 0;
    }

    bool operator<(const pos& other) const {
        return (x < other.x ||( x == other.x && y < other.y));
    }
};

struct rect
{
    uint32_t width;
    uint32_t height;
    void clean()
    {
        width = 0;
        height = 0;
    }
};

enum DisplayState
{
    E_NotDisplay = 0,
    E_Displaying = 1,
};



#endif //DEFINE_H
#ifndef DEFINE_H
#define DEFINE_H
#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include "/home/lisai/jpeg/include/jpeglib.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <linux/input.h>

enum ImageType
{
    UNKNOWN_TYPE,
    BITMAP_TYPE = 0x4D42,
    JPEG_TYPE = 0xFFD8FF,
    PNG_TYPE = 0x474e5089,  
};

struct pos
{
    uint32_t x = 0;
    uint32_t y = 0;
    void clean()
    {
        x = 0;
        y = 0;
    }
};

enum DisplayState
{
    E_NotDisplay = 0,
    E_Displaying = 1,
};



#endif //DEFINE_H
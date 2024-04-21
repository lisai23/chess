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

#define LOGIC_WIDTH 480
#define LOGIC_HEIGHT 800

#define CHESS_WIDTH 9
#define CHESS_HEIGHT 10

enum ImageType
{
    UNKNOWN_TYPE,
    BITMAP_TYPE = 0x4D42,
    JPEG_TYPE = 0xFFD8FF,
    PNG_TYPE = 0x474e5089,  
};

enum PosType
{
    LOGIC_POS = 0,
    SCREEN_POS = 1,
    CHESS_POS = 2,
};

struct pos
{
    uint32_t x;
    uint32_t y;
    PosType type;

    void clean()
    {
        x = 0;
        y = 0;
    }

    bool operator<(const pos& other) const {
        return (x < other.x ||( x == other.x && y < other.y));
    }

    void switchToLogicPos()
    {
        if (LOGIC_POS == type)
        {
            return;
        }
        else if (SCREEN_POS == type)
        {
            uint32_t tmp = x;
            x = y;
            y = 800 - tmp;
            type = LOGIC_POS;
        }
        else if (CHESS_POS == type)
        {
            
        }
        else
        {
            /* code */
        }
        
    }

    void switchToScreenPos()
    {
        if (SCREEN_POS == type)
        {
            return;
        }
        else if (CHESS_POS == type)
        {
            switchToLogicPos();
        }
        else
        {
            /* code */
        }

        uint32_t tmp = x;
        x = 800 - y;
        y = tmp;
        type = SCREEN_POS;
    }

    void switchChessPos()
    {
        if (CHESS_POS == type)
        {
            return;
        }
        else if (SCREEN_POS == type)
        {
            switchToLogicPos();
        }
        else
        {
            /* code */
        }
        


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

enum PiecesType
{
    PiecesType_shuai_red = 0,
    PiecesType_shi_red,
    PiecesType_xiang_red,
    PiecesType_ma_red,
    PiecesType_ju_red,
    PiecesType_pao_red,
    PiecesType_bing_red,

    PiecesType_jiang_black,
    PiecesType_shi_black,
    PiecesType_xiang_black,
    PiecesType_ma_black,
    PiecesType_ju_black,
    PiecesType_pao_black,
    PiecesType_zu_black,
};


#endif //DEFINE_H
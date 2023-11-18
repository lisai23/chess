#include "JPEGHandle.h"

JPEGHandle::JPEGHandle(/* args */)
{
}

JPEGHandle::~JPEGHandle()
{
}

void JPEGHandle::LoadImage(std::string path, Image *img)
{

    //struct fb_var_screeninfo screeninfo;//声明一个与屏幕信息相关的结构体对象
    //int screenWidth,screenHeight;
    //int bytesperpixel;
    unsigned char *pLineColor;
    //unsigned int (*pFrameBuffer)[800];
    int image_width,image_height;
    //声明一个jpeg解压对象
    struct jpeg_decompress_struct dinfo;
    //把jpeg的出错信息关联到进程的标准错误设备上，除非你不关心jpeg库的出错信息
    struct jpeg_error_mgr err;
    dinfo.err=jpeg_std_error(&err);
    //创建一个jpeg解压对象
    jpeg_create_decompress(&dinfo);

    FILE *fp=fopen(path.c_str(),"r");
    if(fp==NULL)
    {
        perror("Cannot open jpeg_file:");
        jpeg_destroy_decompress(&dinfo);
    }
//将jpeg解压对象和jpeg文件流关联起来，意味这jpeg解压对象将从文件流中获取数据
    jpeg_stdio_src(&dinfo,fp);
//获取头部信息
    jpeg_read_header(&dinfo,TRUE);
    image_height=dinfo.image_height;
    image_width=dinfo.image_width;
    std::cout << "w=" << image_width << ",h=" << image_height << ",num=" << dinfo.num_components << std::endl;
    img->setWidth(dinfo.image_width);
    img->setHeight(dinfo.image_height);
    img->setSize(dinfo.image_width*dinfo.image_height*dinfo.num_components);
    img->setDataPointer(new uint32_t[dinfo.image_width*dinfo.image_height]);
    uint32_t *pFrameBuffer = img->getDataPointer();

    dinfo.scale_num = 1;
	dinfo.scale_denom = 1;

    //开始解压
    jpeg_start_decompress(&dinfo);
//申请一个保存jpeg一行颜色数据的缓冲区
    pLineColor=(unsigned char*)malloc(image_width*dinfo.num_components);

//按行读取jpeg图片的数据并处理
    while(dinfo.output_scanline<dinfo.output_height &&
          dinfo.output_scanline<480)
    {
        int col;
        unsigned char *pTmpColor=pLineColor;
        unsigned char red,green,blue;

        //读取一行
        jpeg_read_scanlines(&dinfo,&pLineColor,1);
        //处理一行
        for(col=0;col<800&&col<dinfo.image_width;col++)
        {
            red=*pTmpColor;
            green=*(pTmpColor+1);
            blue=*(pTmpColor+2);
            pTmpColor+=3;
            *(pFrameBuffer+(dinfo.output_scanline-1)*dinfo.image_width+col)=(red<<16)|(green<<8)|blue;
            //pFrameBuffer[dinfo.output_scanline-1][col]=(red<<16)|(green<<8)|blue;
        }
    }

    free(pLineColor);
    jpeg_finish_decompress(&dinfo);
    fclose(fp);
}
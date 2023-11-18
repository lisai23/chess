#include "BMPHandle.h"

BMPHandle::BMPHandle(/* args */)
{
}

BMPHandle::~BMPHandle()
{
}

void BMPHandle::LoadImage(std::string path, Image *img)
{
    int fd_bmp = open(path.c_str(),O_RDWR);
	if (fd_bmp < 0)
	{
		printf("open %s fail!\n",path.c_str());
		printf("**********\n");
		return;
	}

	unsigned char  head[54]={0};
	read(fd_bmp,head,sizeof(head));
	
	//解析头数据 
	unsigned int wide = *((int *)&head[18]);
	unsigned int high  =  head[22] |  head[23]<<8 | head[24]<<16 | head[25]<<24;

    img->setHeight(high);
    img->setWidth(wide);
    img->setSize(high*wide);
	img->setDataPointer(new uint32_t[high*wide]);
    uint32_t *p_data = img->getDataPointer();
	
	printf("wide=%d\n",wide);
	printf("high=%d\n",high);

	char buf_bmp[wide*high*3];
	int buf_lcd[wide*high];
	int buf1[wide*high];

	lseek(fd_bmp,54,SEEK_SET);

	read(fd_bmp,buf_bmp,sizeof(buf_bmp));
	
	for (int i = 0; i < wide*high; i++)
	{
		//把三个bmp像素转换成一个lcd像素
		buf1[i] = buf_bmp[0+i*3]<<0 | buf_bmp[1+i*3]<<8 | buf_bmp[2+i*3]<<16;
	}

	int x=0,y=0;

	//翻转图片
	for (y = 0; y < high; y++)
	{
		for (x = 0; x < wide; x++)
		{
			buf_lcd[x+(high-1-y)*wide]=buf1[x+y*wide];
		}
	}

    memcpy(p_data,buf_lcd,wide*high*4);

	close(fd_bmp);
	return ;
}
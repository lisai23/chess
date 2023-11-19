#include "log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

FILE *g_fp = nullptr;

void log_init()
{
    struct stat info;
    if (stat(LOGPATH,&info) != 0)
    {
        mkdir(LOGPATH,S_IRGRP|S_IWGRP);
    }
    
    g_fp = fopen(CURRENTLOG,"a+");
}

uint32_t countlogfile()
{
    uint32_t count = 0;
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(LOGPATH)) == NULL) {
        printf("Error opening directory\n");
        return -1;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_type == DT_REG) { // only print regular files
            
            std::string name(dirp->d_name);
            if (std::string::npos != name.find(".log",name.size()-4))
            {
                count++;
            }
            
        }
    }
    return count;
}

void currenttime(char *buff)
{
    time_t nowtime;
	//首先创建一个time_t 类型的变量nowtime
	struct tm* p;
	//然后创建一个新时间结构体指针 p 
	time(&nowtime);
	//使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
	p = localtime(&nowtime);
	//由于此时变量nowtime中的系统时间值为日历时间，我们需要调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中。不改的话，可以参照注意事项手动改。
	memset(buff,0,LOGSIZE);
    sprintf(buff,"%02d:%02d:%02d",p->tm_hour,p->tm_min,p->tm_sec);
}

void debug_log(
			const char *logLevel,
			const char *file,
            const char *func,    
            const int   iLine,
            const char *format ,...)  // __VA_ARGS__会把传入的参数以逗号隔开并且匹配到const char *format ,...
{
		static char output[1024]={0};
        va_list arg_list;
        va_start(arg_list,format);
        char timebuff[LOGSIZE] = {0};
        currenttime(timebuff);
        vsnprintf(output,sizeof(output),format, arg_list);
#ifndef __PRINTFILE__
        printf("[%s][%s][%s][%d]:%s\n",timebuff, file, func, iLine, output);
#else
        printf("[%s][%s][%s][%d]:%s\n",timebuff, file, func, iLine, output);
        if (nullptr != g_fp)
        {
            fprintf(g_fp,"[%s][%s][%s][%d]:%s\n",timebuff, file, func, iLine, output);
            fflush(g_fp);
        }
        else
        {
            perror("log file open fail");
        }

        struct stat info;
        if (stat(CURRENTLOG,&info) == 0)
        {
            if (info.st_size > LOGFILESIZE)
            {
                fclose(g_fp);
                g_fp = nullptr;
                uint32_t count = countlogfile();
                char newlogfile[65] = {0};
                sprintf(newlogfile,"%schess%d.log",LOGPATH,count);
                rename(CURRENTLOG,newlogfile);
                g_fp = fopen(CURRENTLOG,"a+");
            }
        }
        else
        {
            perror("get log file size fail");
        }
        
        //printf("[%s][%s][%s][%d]:%s\n",timebuff, file, func, iLine, output);
#endif
        va_end(arg_list);
}
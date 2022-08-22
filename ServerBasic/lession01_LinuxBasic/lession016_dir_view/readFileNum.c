/*
    //打开目录
    #include <sys/types.h>
    #include <dirent.h>
    DIR *opendir(const char *name);
        参数：
            -name: 需要打开的目录的名称
        返回值：
            DIR* 类型，理解为目录流;
            错误返回NULL

    //读取目录内容
    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
        参数：
            -dirp：是opendir返回的结果
        返回值：
            struct dirent:代表读取到的文件的信息
            读取到末尾或者失败，则返回NULL
    //关闭目录
    #include <sys/types.h>
    #include <dirent.h>
    int closedir(DIR *dirp);
        参数：
            -dirp：opendir返回的结果
        返回值：
            成功返回0，否则返回-1

*/
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int getFileNum(const char* path);

//读取某个目录下普通文件的个数
int main(int argc,char * argv[]){

    if(argc<2){
        printf("%s path\n",argv[0]);
        return -1;
    }
    int num = getFileNum(argv[1]);
    printf("the num of this file:%d\n",num);
    return 0;
}

//用于获取目录下所有普通文件的个数
int getFileNum(const char* path){
    //获取名称
    DIR* dir= opendir(path);
    //定义返回普通文件的个数变量
    int num=0;
    if(dir==NULL){
        perror("opendir");
        exit(0);
    }
    struct dirent * ptr; 
    while ((ptr=readdir(dir))!=NULL)
    {
        //获取名称
        char *dname = ptr->d_name;
        if(strcmp(dname,".")==0||strcmp(dname,"..")==0){
            continue;
        }
        //判断是否是普通文件还是目录
        if(ptr->d_type==DT_DIR){
            //目录，则需要继续读取这个目录
            char newpath[256];
            sprintf(newpath,"%s/%s",path,ptr->d_name);
            num+=getFileNum(newpath);
        }
        if(ptr->d_type==DT_REG){
            num++;
        }
    }
    closedir(dir);
    return num;
}
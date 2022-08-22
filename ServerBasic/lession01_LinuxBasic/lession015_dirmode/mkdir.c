/*
    #include <sys/stat.h>
    #include <sys/types.h>

    int mkdir(const char *pathname, mode_t mode);
        作用：创建一个目录
        参数：
            pathname: 创建的文件路径
            mode: 权限，八进制的数,会与掩码进行按位与得到最后的权限
        返回值：
            成功返回0，否则返回-1
    int rmdir(const char* pathname); 只能用于删除空目录
    
*/
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>

int main(){
    int ret = mkdir("newDir",0777);
    if(ret==-1){
        perror("mkdir");
        return -1;
    }
    return 0;
}
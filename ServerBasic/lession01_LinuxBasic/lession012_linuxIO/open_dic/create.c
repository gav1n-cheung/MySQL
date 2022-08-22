/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags, mode_t mode);
        参数：
            - pathname : 要创建的文件路径
            - flags : 对文件的操作权限和其他设置
                - 必选项：O_RDONLY, O_WRONLY, or  O_RDWR 是互斥的
                - 可选项：O_CREAT 如果文件不存在，则会创建新文件
            - mode : 八进制的数，表示文件对新创建出的文件的操作权限,比如:0775(开头0表示为八进制)
                     如果rwx权限都有，则表示为7,就是二进制的111,每一位对应rwx,则r=4,w=2,x=1
            最终的权限是：mode & ~umask (这里假设为普通用户0002,取反就是最大值0777-0002=0775)
                0777  -> 0 111 111 111
              & 0775  -> 0 111 111 101
            ----------------------------
                0775  -> 0 111 111 101

            我们在open函数中设定的mode不一定完全能取到，要和用户掩码取反后做与操作，最后得到的才是真正的权限
            umask 作用就是抹去一些权限，我们也可以修改umask
                ❯ umask 002
                ❯ umask
                002
                ❯ umask 0022
                ❯ umask
                022

            flags参数是一个int类型的数据，占四个字节，32位
            flags 32个位，每一个位就是一个标志位。
            之所以用按位或 | ,则会叠加标志位，使得标志叠加

*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(){
    //创建一个新文件
    int fd = open("create.txt`",O_RDWR | O_CREAT,0777);
    //
    if(fd==-1) perror("open");
    close(fd);
    return 0;
}
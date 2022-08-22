#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    //创建一个用于通信的socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    //客户端绑定本地的ip和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1){
        perror("bind");
        exit(-1);
    }
    //通信
    while(1){
        //接收数据
        char buf[1024]={0};
        int num = recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
        printf("server say:%s\n",buf);
    }
    close(fd);
    return 0;
}

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
    //设置多播属性
    struct in_addr imr_multiaddr;
    //初始化多播地址
    imr_multiaddr.s_addr = inet_addr("239.0.0.10");
    setsockopt(fd,IPPROTO_IP,IP_MULTICAST_IF,&imr_multiaddr,sizeof(imr_multiaddr));
    //初始化客户端的地址信息
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    cliaddr.sin_addr.s_addr = inet_addr("239.0.0.10");
    int num=0;
    //通信
    while(1){
        char buf[128]={0};
        sprintf(buf,"hello client %d\n",num++);
        //发送数据
        sendto(fd,buf,strlen(buf)+1,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
        printf("组播的数据:%s\n",buf);
        sleep(1);
    }
    close(fd);
    return 0;
}

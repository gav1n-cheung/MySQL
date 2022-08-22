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
    //绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1){
        perror("bind");
        exit(-1);
    }
    //通信
    while(1){
        //接收数据
        char buf[1024]={0};
        char ipbuf[16];
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        int num = recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&cliaddr,&len);
        printf("client IP:%s,Port:%d\n",inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,ipbuf,sizeof(ipbuf)),ntohs(cliaddr.sin_port));
        printf("client say:%s\n",buf);
        //发送数据
        sendto(fd,buf,strlen(buf)+1,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
    }
    return 0;
}

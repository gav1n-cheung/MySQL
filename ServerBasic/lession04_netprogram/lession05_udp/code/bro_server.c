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
    //设置广播属性
    int opv = 1;
    setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&opv,sizeof(opv));
    //创建一个广播的地址
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    cliaddr.sin_addr.s_addr = inet_addr("10.20.7.182");
    int num=0;
    //通信
    while(1){
        char buf[128]={0};
        sprintf(buf,"hello client %d\n",num++);
        //发送数据
        sendto(fd,buf,strlen(buf)+1,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
        printf("广播的数据:%s\n",buf);
        sleep(1);
    }
    close(fd);
    return 0;
}

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
    //服务器地址信息
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int num=0;
    //通信
    while(1){
        //发送数据
        char sendchar[128]={0};
        sprintf(sendchar,"hello,i am client %d\n",num++);
        sendto(fd,sendchar,strlen(sendchar)+1,0,(struct sockaddr *)&saddr,sizeof(sendchar));
        //接收数据
        char buf[1024]={0};
        int num = recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
        printf("server say:%s\n",buf);
        sleep(1);
    }
    return 0;
}

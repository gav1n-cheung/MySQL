//TCP通信客户端
#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    //1.创建套接字
    int c_fd = socket(AF_INET,SOCK_STREAM,0);
    if(c_fd==-1){
        perror("socket");
        exit(-1);
    }
    //2.连接服务器端
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // inet_pton(AF_INET,"127.0.0.1",saddr.sin_addr.s_addr);
    saddr.sin_port= htons(9999);
    int ret = connect(c_fd,(struct sockaddr *)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("connect");
        exit(-1);
    }
    char recvData[1024] = {0};
    //3.通信
    while(1){
        char *data;
        scanf("%s",data);
        ret = write(c_fd,data,strlen(data));
        ret = read(c_fd,recvData,sizeof(recvData));
        if(ret==-1){
            perror("read");
            exit(-1);
        }else if(ret>0){
            printf("recv server data:%s\n",recvData);
        }else if(ret==0){
            //表示客户端断开连接
            printf("server closed...\n");
            break;
        }
        sleep(1);
    }
    //4.关闭连接
    close(c_fd);
    return 0;
}
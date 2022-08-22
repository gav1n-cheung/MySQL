#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

int main(){
    unlink("client.sock");
    //1.创建套接字
    int c_fd = socket(AF_LOCAL,SOCK_STREAM,0);
    if(c_fd==-1){
        perror("socket");
        exit(-1);
    }
    //2.绑定本地套接字文件
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path,"client.sock");
    int ret = bind(c_fd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret==-1){
        perror("bind");
        exit(-1);
    }
    //3.连接服务器
    struct sockaddr_un seraddr;
    seraddr.sun_family = AF_LOCAL;
    strcpy(seraddr.sun_path,"server.sock");
    ret = connect(c_fd,(struct sockaddr*)&seraddr,sizeof(seraddr));
    if(ret==-1){
        perror("connect");
        exit(-1);
    }
    int num=0;
    //5. 通信
    while(1){
        //发送数据
        char buf[128];
        sprintf(buf,"hello i am client:%d\n",num++);
        int send_len = send(c_fd,buf,strlen(buf)+1,0);
        printf("client say:%s\n",buf);
        //接收数据
        int recv_len = recv(c_fd,buf,sizeof(buf),0);
        if(recv_len==-1){
            perror("recv");
            exit(-1);
        }else if(recv_len==0){
            printf("server close...\n");
            close(c_fd);
            break;
        }else if(recv_len>0){
            printf("server say:%s\n",buf);
        }
        sleep(1);
    }
    close(c_fd);
    return 0;
}
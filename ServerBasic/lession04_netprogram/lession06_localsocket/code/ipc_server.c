#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

int main(){
    unlink("server.sock");
    //1.创建套接字
    int l_fd = socket(AF_LOCAL,SOCK_STREAM,0);
    if(l_fd==-1){
        perror("socket");
        exit(-1);
    }
    // int opv = 1;
    // setsockopt(l_fd,SOL_SOCKET,SO_REUSEADDR,&opv,sizeof(opv));
    //2.绑定本地套接字文件
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path,"server.sock");
    int ret = bind(l_fd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret==-1){
        perror("bind");
        exit(-1);
    }
    //3.监听
    ret = listen(l_fd,100);
    if(ret==-1){
        perror("listen");
        exit(-1);
    }
    //4.等待客户端连接
    struct sockaddr_un cliaddr;
    int len = sizeof(cliaddr);
    int c_fd = accept(l_fd,(struct sockaddr*)&cliaddr,&len);
    if(c_fd==-1){
        perror("accpet");
        exit(-1);
    }
    printf("client socket filename:%s\n",cliaddr.sun_path);
    //5. 通信
    while(1){
        char buf[128];
        int recv_len = recv(c_fd,buf,sizeof(buf),0);
        if(recv_len==-1){
            perror("recv");
            exit(-1);
        }else if(recv_len==0){
            printf("client close...\n");
            close(c_fd);
            break;
        }else if(recv_len>0){
            printf("client say:%s\n",buf);
            send(c_fd,buf,sizeof(buf),0);
        }
    }
    close(l_fd);
    return 0;
}
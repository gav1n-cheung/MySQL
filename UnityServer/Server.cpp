#include "Server.h"

TcpServer::TcpServer(){
    m_fd = socket(AF_INET,SOCK_STREAM,0);
}

TcpServer::~TcpServer(){
    close(m_fd);
}

int TcpServer::setListen(unsigned short port){
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_aton("10.0.16.8",&saddr.sin_addr);
    int ret = bind(m_fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("bind failed");
        return -1;
    }
    cout<<"socket bind success\n\tIP:"
        <<inet_ntoa(saddr.sin_addr)
        <<"\n\tPort:"<<port<<endl;
    ret = listen(m_fd,128);
    if(ret == -1){
        perror("listen failed");
        return -1;
    }
    cout<<"listen success..."<<endl;
    return ret;
}

TcpSocket* TcpServer::acceptConn(sockaddr_in *addr){
    if(addr == NULL) return nullptr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int cfd = accept(m_fd,(struct sockaddr*)addr,&addrlen);
    if(cfd == -1){
        perror("accept");
        return nullptr;
    }
    cout<<"connet success..."<<endl;
    return new TcpSocket(cfd);
}
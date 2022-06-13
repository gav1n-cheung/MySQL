#include "translate.h"

TcpSocket::TcpSocket(){
    m_fd = socket(AF_INET,SOCK_STREAM,0);
}

TcpSocket::TcpSocket(int socket){
    m_fd = socket;
}

TcpSocket::~TcpSocket(){
    if(m_fd>0) close(m_fd);
}

int TcpSocket::connectToHost(string ip,unsigned short port){
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_pton(AF_INET,ip.data(),&saddr.sin_addr.s_addr);
    int ret = connect(m_fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("connect failed!");
        return -1;
    }
    cout<<"connect success!"<<endl;
    return ret;
}

int TcpSocket::sendMsg(string msg){
    char* data = new char[msg.size()+4];
    int bigLen = htonl(msg.size());
    memcpy(data,&bigLen,4);
    memcpy(data+4,msg.data(),msg.size());
    int ret = writen(data,msg.size()+4);
    delete[]data;
    return ret;
}

string TcpSocket::recvMsg(){
    //接收数据
    //1、读数据头
    int len = 0;
    readn((char*)&len,4);
    len = ntohl(len);
    cout<<"size of data cube: "<<len<<endl;
    //根据读出的长度分配内存
    char* buf = new char[len+1];
    int ret = readn(buf,len);
    if(ret!=len) return string();
    buf[len] = '\0';
    string retStr(buf);
    delete[] buf;
    return retStr;
}

int TcpSocket::readn(char* buf, int size)
{
    int nread = 0;
    int left = size;
    char* p = buf;

    while (left > 0)
    {
        if ((nread = read(m_fd, p, left)) > 0)
        {
            p += nread;
            left -= nread;
        }
        else if (nread == -1)
        {
            return -1;
        }
    }
    return size;
}

int TcpSocket::writen(const char* msg, int size)
{
    int left = size;
    int nwrite = 0;
    const char* p = msg;

    while (left > 0)
    {
        if ((nwrite = write(m_fd, msg, left)) > 0)
        {
            p += nwrite;
            left -= nwrite;
        }
        else if (nwrite == -1)
        {
            return -1;
        }
    }
    return size;
}

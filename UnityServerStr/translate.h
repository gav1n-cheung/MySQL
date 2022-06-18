#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;
class TcpSocket{
    public:
        TcpSocket();
        TcpSocket(int socket);
        ~TcpSocket();
        int connectToHost(string ip,unsigned short port);
        int sendMsg(string msg);
        string recvMsg();
    private:
        int readn(char* buf,int size);
        int writen(const char* msg,int size);
    private:
        int m_fd;
};

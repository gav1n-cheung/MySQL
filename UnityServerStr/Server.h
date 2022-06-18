#include "translate.h"

class TcpServer{
    public:
        TcpServer();
        ~TcpServer();
        int setListen(unsigned short port);
        TcpSocket* acceptConn(struct sockaddr_in* addr = nullptr);
    private:
        int m_fd;
};
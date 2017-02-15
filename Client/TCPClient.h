//
// Created by munk on 15-02-17.
//

#ifndef CLIENT_SERVER_SOCKET_TCPCLIENT_H
#define CLIENT_SERVER_SOCKET_TCPCLIENT_H

#include <sys/socket.h>

#define IPSIZE 14

class TCPClient {
public:
    TCPClient();
    int initClient();

private:
    char ip[IPSIZE] = {'1','0','.','0','.','0','.','1'};
    int tcpSocket;
};


#endif //CLIENT_SERVER_SOCKET_TCPCLIENT_H

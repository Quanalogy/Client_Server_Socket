//
// Created by munk on 15-02-17.
//

#ifndef CLIENT_SERVER_SOCKET_TCPCLIENT_H
#define CLIENT_SERVER_SOCKET_TCPCLIENT_H

#include <sys/socket.h>
#include <netdb.h>

class TCPClient {
public:
    TCPClient();
    int initClient();
    ssize_t sendToServer(const void *msg, size_t length);
private:
    int tcpSocket;
    const char *IPAddr;
    const char *PortNr;
    struct addrinfo hints;
    struct addrinfo *serverinfo;
};


#endif //CLIENT_SERVER_SOCKET_TCPCLIENT_H

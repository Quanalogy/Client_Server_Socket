//
// Created by munk on 15-02-17.
//

#ifndef CLIENT_SERVER_SOCKET_TCPCLIENT_H
#define CLIENT_SERVER_SOCKET_TCPCLIENT_H

#include <sys/socket.h>
#include <netdb.h>

class TCPClient {
public:
    /*!
     * Setup constants
     */
    TCPClient();

    /*!
     * Send a message to the server
     * @param msg The message: write dir for a list of files to get
     * @param length The length of the message
     * @return 0 on success otherwise standard error
     */
    ssize_t sendToServer(const void *msg, size_t length);

    ssize_t receiveFromServer(char ***buf);
    ssize_t receiveFileFromServer(const char *filename);
    void getIP(char **ip);
    void getPort(char **port);
    void setIp(char *ip);
    void setPort(char *port);
private:
    int tcpSocket;
    char const *IPAddr;
    char const *PortNr;
    struct addrinfo hints;
    struct addrinfo *serverinfo;
};


#endif //CLIENT_SERVER_SOCKET_TCPCLIENT_H

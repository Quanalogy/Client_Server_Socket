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
     * Init the Client
     * @return 0 on success otherwise standard error
     */
    int initClient();

    /*!
     * Send a message to the server
     * @param msg The message
     * @param length The length of the message
     * @return 0 on success otherwise standard error
     */
    ssize_t sendToServer(const void *msg, size_t length);

    ssize_t receiveFromServer(char *buf);
private:
    int tcpSocket;
    const char *IPAddr;
    const char *PortNr;
    struct addrinfo hints;
    struct addrinfo *serverinfo;
};


#endif //CLIENT_SERVER_SOCKET_TCPCLIENT_H

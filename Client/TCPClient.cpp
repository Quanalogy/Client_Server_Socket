//
// Created by munk on 15-02-17.
//

#include "TCPClient.h"
#include <iostream>
#include <cstring>

using namespace std;
TCPClient::TCPClient() {
    cout << "Initializing client..." << endl << "Creating socket..." << endl;
    IPAddr = "127.0.0.1";
    PortNr = "12000";
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
}

int TCPClient::initClient() {
    // Make ip and port in readable format for the socket
    int status = getaddrinfo(IPAddr, PortNr, &hints, &serverinfo);

    if(status != 0){
        cout << "Problems assigning the server to the ip" << endl << gai_strerror(status) << endl;
        return status;
    }
}

ssize_t TCPClient::sendToServer(const void *msg, size_t length) {
    // create a socket for ip and port
    tcpSocket = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
    if(tcpSocket <= 0){
        cout << "Failed creation of socket" << endl << tcpSocket << endl;
        return tcpSocket;
    } else {
        cout << "Successfully created the socket..." << endl;
    }

    // Connect to the server
    int error = connect(tcpSocket, serverinfo->ai_addr, serverinfo->ai_addrlen);
    if(error == -1) {
        cout << "An error occured when connecting to the server, dropping connection.. :(" << endl
             << gai_strerror(error) << endl;
        return error;
    } else {
        cout << "Connected to the server..." << endl;
    }

    // Send the message
    return send(tcpSocket, msg, length, 0);
}
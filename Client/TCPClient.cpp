//
// Created by munk on 15-02-17.
//

#include "TCPClient.h"
#include <iostream>

using namespace std;
TCPClient::TCPClient() {
    cout << "Initializing client..." << endl << "Creating socket..." << endl;
}

int TCPClient::initClient() {
    // create a socket with standard setup of:
    // network connection,
    // continuous stream of data
    // and default protocol (0)
    tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcpSocket <= 0){
        cout << "Failed creation of socket" << endl << tcpSocket << endl;
        return tcpSocket;
    } else {
        cout << "Successfully created the socket..." << endl;
    }


    const sockaddr tcpAddress = {AF_INET, {*ip}};

    int error = connect(tcpSocket, &tcpAddress, sizeof(tcpAddress));
    if(error == -1) {
        cout << "An error occured when connecting to the server, dropping connection.. :(" << endl
             << error << endl;
        return error;
    } else {
        cout << "Connected to the server..." << endl;
    }
}
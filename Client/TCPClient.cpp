//
// Created by munk on 15-02-17.
//

#include "TCPClient.h"
#include <iostream>
#include <cstring>

using namespace std;
TCPClient::TCPClient() {
    IPAddr = "127.0.0.1";
//    IPAddr = "172.20.10.9";;
    PortNr = "9000";
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
}

ssize_t TCPClient::sendToServer(const void *msg, size_t length) {
    int status = getaddrinfo(IPAddr, PortNr, &hints, &serverinfo);

    if(status != 0){
        cout << "Problems assigning the server to the IP" << endl << gai_strerror(status) << endl;
        return status;
    }

    // create a socket for ip and port
    tcpSocket = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
    if(tcpSocket <= 0){
        cout << "Failed creation of socket" << endl << tcpSocket << endl;
        return tcpSocket;
    }

    // Connect to the server
    int error = connect(tcpSocket, serverinfo->ai_addr, serverinfo->ai_addrlen);
    if(error == -1) {
        cout << "An error occurred while connecting to the server, dropping connection.. :(" << endl
             << strerror(errno) << endl;
        return error;
    }

    // Send the message
    return send(tcpSocket, msg, length, 0);

}


ssize_t TCPClient::receiveFileFromServer(const char *filename) {

    size_t bufSize = 256;
    char filesizeBuf[bufSize];
    // Get size of file to receive
    ssize_t bytesReceived = recvfrom(tcpSocket, filesizeBuf, bufSize, 0,
                                        serverinfo->ai_addr, &serverinfo->ai_addrlen);

    if(bytesReceived == -1) {
        cout << "Error receiving filesize, with error: " << strerror(errno) << endl;
        return bytesReceived;
    }

    ssize_t remainingData = atol(filesizeBuf);

    cout << "Filesize is: " << filesizeBuf << " and atoi: " << remainingData << endl;
    if(remainingData == 404){           // File not found
        cout << "File not found, please send a location which corresponds to an existing file" << endl;
        return -1;
    } else if (remainingData == 400) {  // Bad request - directory
        cout << "You have requested a directory, this is not allowed, returning!" << endl;
        return -1;
    }

    FILE *file = fopen64(filename, "wb");

    if(file == NULL) {
        cout << "Failed to give write permissions for new received file!! Error: " << strerror(errno) << endl;
        return -1;
    } else {
        cout << "Successfully opened file" << endl;
    }

    bufSize = 1000;

    char fileBuffer[bufSize];

    while(remainingData > 0) {
        if(remainingData < 1000) {
            bufSize = (size_t) remainingData;
        }


        bytesReceived = recvfrom(tcpSocket, fileBuffer, bufSize, 0,
                                    serverinfo->ai_addr, &serverinfo->ai_addrlen);

        if(bytesReceived == -1) {
            cout << "Error receiving the file, with error: " << strerror(errno) << endl;
        } else {
//            cout << "Got " << bytesReceived << " bytes" << endl;
            size_t filebytes = fwrite(fileBuffer, sizeof(char), bytesReceived, file);
            if(filebytes == -1){
                cout << "Error Writing to the file" << endl;
            } else {
//                cout << "Wrote " << filebytes << " bytes" << endl;
            }
        }

        remainingData -= bytesReceived;
    }
    fclose(file);
    cout << "File retrieved, with " << remainingData << " remaining bytes" << endl;
    return bytesReceived;
}

ssize_t TCPClient::receiveFromServer(char ***buf) {

    // Receive an size_t describing how many elements to expect.
    char elementBuf[sizeof(size_t)];
    size_t elements = 0;
    ssize_t wordsToRecv = recvfrom(tcpSocket, elementBuf, sizeof(size_t), 0,
                                   serverinfo->ai_addr, &serverinfo->ai_addrlen);

    if(wordsToRecv == -1){
        cout << "Error receiving number of dir elements, quitting with error: "
             << strerror(errno) << endl;
        return 0;
    } else {
        elements = (size_t) atoi(elementBuf);
        cout << "This is the size: " << elements << endl;
    }

    *buf = (char **) calloc(elements, (sizeof(char *)));

    char *recvBuffer;
    ssize_t bytesRecv = 1;

    int index = 0;
    while(bytesRecv != 0) {
        size_t len = 0;

        bytesRecv = recvfrom(tcpSocket, &len, sizeof(len), 0,
                             serverinfo->ai_addr, &serverinfo->ai_addrlen);
        if(bytesRecv == -1) {
            cout << "Failed receiving the size of elements: " << strerror(errno) << endl;
        }

        recvBuffer = (char *) calloc(len, sizeof(char *));

        bytesRecv = recvfrom(tcpSocket, &recvBuffer[0], len, 0,
                             serverinfo->ai_addr, &serverinfo->ai_addrlen);
        if(bytesRecv == -1) {
            cout << "Failed receiving the elements: " << strerror(errno) << endl;
        } else {
            recvBuffer[bytesRecv] = '\0';
            (*buf)[index] = strdup(recvBuffer);
//            cout << "bytesreceived: " << bytesRecv << " of: " << recvBuffer<< endl
//                    << "Copy: " << (*buf)[index] << endl;
        }
//        index += bytesRecv;
        index++;
    }

    cout << "end, now total:" << endl;
    for (int j = 0; j < elements; ++j) {
        cout << (*buf)[j] << endl;
    }

    return bytesRecv;
}

void TCPClient::getIP(char **ip) {
    *ip = (char *) malloc(strlen(IPAddr)*sizeof(char));
    snprintf(*ip, strlen(IPAddr)+1, "%s", IPAddr);
}

void TCPClient::getPort(char **port) {
    *port = (char *) malloc(strlen(PortNr)* sizeof(char));
    snprintf(*port, strlen(PortNr)+1, "%s", PortNr);
}

void TCPClient::setIp(char *ip) {
    IPAddr = ip;
    cout << "Ip set to: " << IPAddr << endl;
}

void TCPClient::setPort(char *port) {
    PortNr = port;
    cout << "Port set to: " << PortNr << endl;
}
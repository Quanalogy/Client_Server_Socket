#include <iostream>
#include <sys/socket.h>

#define IPSIZE 14
char ip[IPSIZE] = {'1','0','.','0','.','0','.','1'};

using namespace std;
int main() {
    cout << "Initializing client..." << endl << "Creating socket..." << endl;

    // create a socket with standard setup of:
    // network connection,
    // continuous stream of data
    // and default protocol (0)
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcpSocket <= 0){
        cout << "Failed creation of socket" << endl << tcpSocket << endl;
        return tcpSocket;
    } else {
        cout << "Successfully created the socket..." << endl;
    }

    string message;
    cout << "Insert message to send to the server on IP: " << ip << endl;
    getline(cin, message);
    cout << "You've entered: " << message << endl;

    const sockaddr tcpAddress = {AF_INET, {*ip}};

    int error = connect(tcpSocket, &tcpAddress, IPSIZE);
    if(error == -1) {
        cout << "An error occured when connecting to the server, dropping connection.. :(" << endl
                << error << endl;
        return error;
    } else {
        cout << "Connected to the server..." << endl;
    }


    return 0;
}
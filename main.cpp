#include <iostream>
#include "Client/TCPClient.h"

using namespace std;
int main() {

    TCPClient client;

    client.initClient();
    string message;
    char recvMessage[1000] = {0};
    while(1) {
        cout << "Insert message to send to the server" << endl;
        getline(cin, message);
        size_t length = message.length();
        cout << "You've entered: " << message << " in a size of: " << length << endl;
        ssize_t returnlegth = client.sendToServer(&message[0], length);
        if(returnlegth == -1){
            cout << "Error sending message to server" << endl;
        } else if (returnlegth != length){
            cout << "Not all of the message came through" << endl;
        } else {
            cout << "The total message were delivered - nice!" << endl;
        }
        cout << "size from server: " << client.receiveFromServer(recvMessage) << endl;

    }

    //return 0;
}

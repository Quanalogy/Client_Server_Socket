#include <iostream>
#include "Client/TCPClient.h"

using namespace std;
int main() {

    TCPClient client;

    client.initClient();
    string message;
    while(1) {
        cout << "Insert message to send to the server" << endl;
        getline(cin, message);
        cout << "You've entered: " << message << endl;
        size_t length = message.length();
        ssize_t returnlegth = client.sendToServer(&message, length);
        if(returnlegth == -1){
            cout << "Error sending message to server" << endl;
        } else if (returnlegth != length){
            cout << "Not all of the message came through" << endl;
        } else {
            cout << "The total message were delivered - nice!" << endl;
        }

    }

    //return 0;
}
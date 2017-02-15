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
    }

    //return 0;
}
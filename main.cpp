#include <iostream>
#include <cstring>
#include <zconf.h>
#include "Client/TCPClient.h"

using namespace std;

int main() {

    TCPClient client;
    string message;
    char **recvMessage;
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL){
        cout << "Saving files to folder: " << cwd << endl;
    }
    cout << "Hi! Welcome to the TCPClient, from here you can get a file on the server!" << endl;
    while (1) {
        int choice;
        do {
                 cout << "Choose either:" << endl
                 << "1. Get a file with a path to the given file" << endl
                 << "2. List the directory of a path and then get a file from it" << endl
                 << "3. Exit" << endl << "Please enter a number corresponding to what you want to do" << endl;
            cin >> choice;
        } while (choice < 1 || choice > 3);


        if (choice == 3) {
            return 0;
        } else if (choice == 1) { // Get file at path
            cout << "Insert path to file to get from server" << endl;
            do {
                getline(cin, message);
            } while (message.length() == 0);

            size_t length = message.length();

            ssize_t fileIndex = message.find_last_of("/");
            string filename = message.substr(fileIndex+1, message.length());
            string folder = message.substr(0, fileIndex);
            cout << "You want the file: " << filename << " in the folder: " << folder << endl;

            ssize_t returnlength = client.sendToServer(&message[0], length);
            if(returnlength == -1){
                cout << "Error sending message to server" << endl;
            } else if (returnlength != length){
                cout << "Not all of the message came through" << endl;
            }

            strcat(cwd, "/");
            strcat(cwd, filename.c_str());

            cout << "Getting file and saving it in path: " << cwd << endl;

            client.receiveFileFromServer(cwd);
        } else {
            client.sendToServer("dir", 3);
            client.receiveFromServer(&recvMessage);
        }

    }

    //return 0;
}


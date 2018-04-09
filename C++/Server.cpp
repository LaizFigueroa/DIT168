#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

using namespace std;
int SOCKET_BUFFER_SIZE=1024;
socklen_t *addrlen;
socklen_t *connectClient;
fd_set readfds;



int main() {
    sockaddr_in server_addr;

    int  server;
    socklen_t size = sizeof(server_addr);


    server = socket(AF_INET, SOCK_DGRAM, 0);


    if (server == -1) {
        cout << "\n Error establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("10.132.27.127");


    server_addr.sin_port = htons(8080);

    printf("Waiting for a connection...");

    bind(server, (sockaddr *)&server_addr, size);

    cout << "=> Looking for clients..." << endl;

    /**
     * currently not needed due to UDP coomunication protocol
     */
/**
    int listen_client = listen(server, 1);

    if (listen_client < 0) {
        cerr << "Cannot open socket" << endl;
    }


        cout << "=> trying to accept clients..." << endl;

        int client = accept(server, (struct sockaddr *) &server_addr, connectClient);

        cout << "=> Accepting clients..." << endl;

        if (client < 0) {

            perror("Accept failed");
        } else {
            printf("Accept client socket");

        }
        cout << "=> CLIENT ACCPTED ..." << endl;

        // first check if it is valid or not
        if (server < 0)
            cout << "=> Error on accepting..." << endl;

**/

    /**
     * this while loop continously listening to data from the java client
     */
    while (1) {

        char buffer[SOCKET_BUFFER_SIZE];
        int command;
        int returnvalue=0;
        string data;
        size_t pos = 0;

        // empty messagestring
        string message = "";

        // empty buffer
        memset(buffer, 0, sizeof(buffer));



        while (1) {
            cout << "before  ..." << endl;


            if(recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size)< 0) // recvfrom() function call
            {
                cout  << "Fatal: Failed to receive data"  << endl;
                break;
            }
            else

            cout << "=> start ..." << endl;


            cout << command << endl;
            cout << "received: " << buffer << endl;

            message.append(buffer);

            std::string delimiter = "//";

            while ((pos = message.find(delimiter)) != std::string::npos) {
                // while (message!=NULL) {

                data = message.substr(0, pos);
                std::cout << data << std::endl;
                message.erase(0, pos + delimiter.length());

                memset(buffer, 0, sizeof(buffer));

                cout << "message is now: " << message << endl;

            }
            buffer[strlen(buffer) - 1] = '\0';
        }


    }


    }



#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
int SOCKET_BUFFER_SIZE=10;


int main() {
    sockaddr_in server_addr;
    int  server;
    socklen_t size = sizeof(server_addr);


    server = socket(AF_INET, SOCK_STREAM, 0);


    if (server == -1) {
        cout << "\n Error establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);

    printf("Waiting for a connection...");

    bind(server, (sockaddr *)&server_addr, sizeof(server_addr));

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

        int client = accept(server, (struct sockaddr *) &server_addr, &size);

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
        string data;
        size_t pos = 0;

        // empty messagestring
        string message = "";

        // empty buffer
        memset(buffer, 0, sizeof(buffer));


        while ((command = recvfrom(server, buffer, size, 0, (struct sockaddr *)&server_addr, reinterpret_cast<socklen_t *>(size)) > 0)) {
            cout << "=> start ..." << endl;


            cout << command << endl;
            cout << "received: " << buffer << endl;

            message.append(buffer);

            std::string delimiter = "//";

            while ((pos = message.find(delimiter)) != std::string::npos) {
                data = message.substr(0, pos);
                std::cout << data << std::endl;
                message.erase(0, pos + delimiter.length());

                memset(buffer, 0, sizeof(buffer));

                cout << "message is now: " << message << endl;

            }


        }


    }

}
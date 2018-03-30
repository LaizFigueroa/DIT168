
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;



int main() {
    sockaddr_in server_addr;
    int  server;
    bool isExit = false;
    char incoming_data[1024];
    socklen_t size = sizeof(server_addr);


    server = socket(AF_INET, SOCK_STREAM, 0);


    if (server == -1) {
        cout << "\n Error establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    printf("Waiting for a connection...");

    bind(server, (sockaddr *)&server_addr, sizeof(server_addr));

   // if (     ){

      //  cout << "=> Error binding connection, the socket has already been established..." << endl;
  //  }

    cout << "=> Looking for clients..." << endl;


    int listen_client = listen(server, 1);

    if (listen_client < 0) {
        cerr << "Cannot open socket" << endl;
    }


    int clientCount = 1;


    int client = accept (server, (struct sockaddr *) &server_addr, &size);


    if (client < 0) {

        perror("Accept failed");
    } else {
        printf("Accept client socket");

    }

    // first check if it is valid or not
    if (server < 0)
        cout << "=> Error on accepting..." << endl;



}

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
    int buffer_size=10;
    int serverport=8081;
    
    socklen_t size = sizeof(server_addr);
    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server == -1) {
        cout << "\n Error establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(serverport);
    
    cout << "Waiting for a connection..." <<endl;

    bind(server, (sockaddr *)&server_addr, sizeof(server_addr));
    cout << "=> Wating for clients..." << endl;


    int listen_client = listen(server, 1);
    if (listen_client < 0) {
        cerr << "Cannot open socket" << endl;
    }

// Loop for handling the reconnection, when disconnection with client happeneds.
    while(1){
        
    int client = accept (server, (struct sockaddr *) &server_addr, &size);
    if (client < 0) {

        cerr << "Accept failed" <<endl;
    } else {
        cout << "Accept client socket" <<endl;
    }

    // first check if it is valid or not
    if (server < 0)
        cout << "=> Error on accepting..." << endl;
   
    //create buffer for the data
    char buf[buffer_size];
    // the stuct for the size of the buffer
    ssize_t bytes_read;
    
    // loop for reciving
    while(1){
        //read buffer
       bytes_read=recv(client, buf, sizeof(buf), 0);
        // incase the client dissconnects break the loop
        if (bytes_read==0)
            break;
        // else EXECUTING THE commmands
        cout << buf;
        
            // STOP CAR
            if (buf == 0){
                
            }
        
            // MOVE FORWARD
            if (buf == 1){
                
            }
            // MOVE LEFT
            if (buf == 2){
                
            }
            // MOVE RIGHT
            if (buf == 3){
                
            }
        
        // flush the buffer
        memset (buf,0,buffer_size);
    }
        cout << "client disconnected" <<endl;
    close(client);
    }
    close(server);

}

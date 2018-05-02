#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <thread>


using namespace std;
int SOCKET_BUFFER_SIZE = 1024;
socklen_t *addrlen;
float imu_value;

int main() {
    sockaddr_in server_addr;
    int server;
    socklen_t size = sizeof(server_addr);
    server = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (server == -1) {
        cout << "\n Error establishing socket..." << endl;
        exit(1);
    }
    
    cout << "\n=> Socket server has been created..." << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(50002);
    bind(server, (sockaddr * ) & server_addr, size); // bind
    
    /**
     * The loop continously listening to data from the client IMU
     */
    
    char buffer[SOCKET_BUFFER_SIZE];
    while (1) {
        
        size_t array = sizeof(buffer);
        cout << "\n Clearing buffer before receving ... " << endl;
        memset(buffer, 0, sizeof(buffer));
        recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size);
        
        if (recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size) < 0) // recvfrom() function call
        {
            cout << "\n Fatal: Failed to receive data .. " << endl;
            break;
        } else{
            
            // converting string to float
            imu_value = stof(buffer);
            cout << "IMU VALUE IS :  " << imu_value << endl;
            // cleaning the buffer
            memset(buffer, 0, array);
            
        }
    }
}

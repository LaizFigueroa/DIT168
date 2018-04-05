
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


// libraries for the commands
#include <cstdint>
#include <chrono>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"


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
     
        cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) noexcept {
            if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
                opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
                std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
            }
            else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
                opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
                std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
            }
        });
        
        if(od4.isRunning() == 0)
        {
            std::cout << "ERROR: No od4 running!!!" << std::endl;
            return -1;
        }
        
        opendlv::proxy::GroundSteeringReading msgSteering;
        opendlv::proxy::PedalPositionReading msgPedal;
        
        const int delay = 1000;
        
            // STOP CAR
            if (buf[0] == 0){
               
                    std::cout << "Now Stop ..." << std::endl;
                    msgPedal.percent(0.0);
                    od4.send(msgPedal);
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    
            }
        
            // MOVE FORWARD
            if (buf[0] == 1){
                std::cout << " move forward ..." << std::endl;
                msgSteering.steeringAngle(0.0);
                od4.send(msgSteering);
                msgPedal.percent(0.4);
                od4.send(msgPedal);
                std::this_thread::sleep_for(std::chrono::milliseconds(2 * delay));
            }
            // MOVE LEFT
            if (buf[0] == 2){
                std::cout << "turn left a little bit ..." << std::endl;
                msgPedal.percent(0.2);
                od4.send(msgPedal);
                msgSteering.steeringAngle(-15.0);
                od4.send(msgSteering);
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
            // MOVE RIGHT
            if (buf[0] == 3){
                std::cout << "Turn right a little bit ..." << std::endl;
                msgSteering.steeringAngle(15.0);
                od4.send(msgSteering);
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
        
        // flush the buffer
        memset (buf,0,buffer_size);
    }
        cout << "client disconnected" <<endl;
    close(client);
    }
    close(server);

}

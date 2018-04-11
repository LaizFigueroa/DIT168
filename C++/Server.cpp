#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <thread>

/* libraries for the commands */
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"


using namespace std;
int SOCKET_BUFFER_SIZE = 1024;
socklen_t *addrlen;
int on=1;
string speed;
string angle;

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
    //10.132.27.127
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.249");
    server_addr.sin_port = htons(8080);
    bind(server, (sockaddr * ) & server_addr, size);
    
    /**
     * this while loop continously listening to data from the java client
     */
    while (1) {
        int command;
        int returnvalue=0;
        char buffer[SOCKET_BUFFER_SIZE];
        size_t pos = 0;

        // the message that contains the command
        string message = "";

        while (1) {

            char * element;
            size_t i;
            size_t array = sizeof(buffer);

            cout << "before  ..." << endl;
            memset(buffer, 0, sizeof(buffer));

            if (recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size) < 0) // recvfrom() function call
            {
                cout << "Fatal: Failed to receive data" << endl;
                break;
            } else

                cout << "=> start ..." << endl;
            cout << buffer << endl;
            buffer[strlen(buffer)] = '\0';
            char* end_of_buffer = buffer;
            std::size_t remaining_space = sizeof(buffer);

            message=buffer;
            //message.append(buffer);
            cout << "the incoming stream : " << message << endl;

            std::string delimiter = "//";
            while ((pos = message.find(delimiter)) != std::string::npos) {

                angle = message.substr(0, pos);
                std::cout << angle << std::endl;
                message.erase(0, pos + delimiter.length());
                speed =message;
                cout << "message isa now: " << angle << "/" << speed <<  endl;

            }
            memset(buffer, 0, array);
            //buffer[SOCKET_BUFFER_SIZE] ; // buff is full of zeros




            if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0)
            {
                perror("cannot unbind") ;
            }

                
                // converting string to float
                float anglef = stof(angle);
                float speedf = stof(speed);
                
                cluon::OD4Session od4(111, [](cluon::data::Envelope && envelope) noexcept {
                    if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
                        opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage < opendlv::proxy::GroundSteeringReading > (std::move(envelope));
                        std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
                    } else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
                        opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage < opendlv::proxy::PedalPositionReading > (std::move(envelope));
                        std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
                    }
                });
                
                if (od4.isRunning() == 0) {
                    std::cout << "ERROR: No od4 running!!!" << std::endl;
                    return -1;
                }
                
                opendlv::proxy::GroundSteeringReading msgSteering;
                opendlv::proxy::PedalPositionReading msgPedal;
                const int delay = 1000;
                
                // HANDELING MOVMENT
                std::cout << " EXECUTING SOME MOVEMENTS ..." << std::endl;
                msgSteering.steeringAngle(anglef);
                od4.send(msgSteering);
                msgPedal.percent(speedf);
                od4.send(msgPedal);
                std::this_thread::sleep_for(std::chrono::milliseconds(2 * delay));
                
            }
           // buffer[strlen(buffer) - 1] = '\0';
        }
    }
    
}

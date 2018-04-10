#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

/* libraries for the commands */
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"


using namespace std;
int SOCKET_BUFFER_SIZE = 1024;

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
        char buffer[SOCKET_BUFFER_SIZE];
        int returnvalue = 0;
        string angle;
        size_t pos = 0;
        
        // empty speedstring
        string speed = "";
        // empty buffer
        memset(buffer, 0, sizeof(buffer));
        
        // loop for reciving the data
        while (1) {
            // recvfrom() function call
            if (recvfrom(server, & buffer, sizeof(buffer), 0, (struct sockaddr * ) & server_addr, & size) < 0) {
                cout << "Fatal: Failed to receive data" << endl;
                break;
            } else
                cout << "received: " << buffer << endl;
            speed.append(buffer);
            std::string delimiter = "//";
            
            // loop for gathering the speed
            while ((pos = speed.find(delimiter)) != std::string::npos) {
                angle = speed.substr(0, pos);
                std::cout << "angle: " << angle << std::endl;
                
                speed.erase(0, pos + delimiter.length());
                memset(buffer, 0, sizeof(buffer));
                cout << "speed: " << speed << endl;
                
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
            buffer[strlen(buffer) - 1] = '\0';
        }
    }
    
}

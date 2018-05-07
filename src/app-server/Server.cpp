// Copyright (C) 2018 DIT168 - Group 13
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Created by Rema Salman on 2018-04-28.
//
// Refrences used : - The UDP server is, avalible on: <https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html>
//                  - Splitting the buffer message, avalible on: <https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c>

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


using namespace std; // Name space declaration
/* Variabuls declaration*/
int SOCKET_BUFFER_SIZE = 1024;
socklen_t *addrlen;
string speed;
string angle;  // the message that contains the full commands
string message = "";

const int delay = 100; // Delay for sending the messages
static const int COMMANDS_CHANNEL    = 242;
static const int INTERNAL_CHANNEL    = 240;

cluon::OD4Session od4(COMMANDS_CHANNEL, [](cluon::data::Envelope && envelope) noexcept {});

/* The main executing of the program */
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
//Set up the socket IP family to AF_INET
server_addr.sin_family = AF_INET;
// Socket's IP address
server_addr.sin_addr.s_addr = inet_addr("172.20.10.2");
// Port used for transporting the data
server_addr.sin_port = htons(8080);
//binding a unique name to the descriptor socket
bind(server, (sockaddr * ) & server_addr, size);
// buffer's deceleration
char buffer[SOCKET_BUFFER_SIZE];

/**
  * This while loop continously listening to data from the java client
*/
while (1) {
    size_t pos = 0  ;
    size_t array = sizeof(buffer);
    cout << "before  ..." << endl;
    // Clear the buffer
    memset(buffer, 0, sizeof(buffer));
    // receive function for an incoming datagram
    recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size);
        
    // Side case failler  of receiving
    if (recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size) < 0) {
        cout << "Fatal: Failed to receive data" << endl;
        break;
    } else {
        // Checking the buffer when receiving
        buffer[strlen(buffer)] = '\0';
        char* end_of_buffer = buffer;
        size_t remaining_space = sizeof(buffer);
        message=buffer;
        cout << "the incoming stream : " << message << endl;

        // Separating the string command into 2 strings angle and speed
        string delimiter = "//";
        while ((pos = message.find(delimiter)) != string::npos) {
            angle = message.substr(0, pos);
            cout << angle << endl;
            message.erase(0, pos + delimiter.length());
            speed =message;
            cout << "message is: " << angle << "/" << speed <<  endl;
        }
        // clear the buffer
        memset(buffer, 0, array);
        // converting received string to float
        float anglef = stof(angle);
        float speedf = stof(speed);
        
        // Declaring and initializing the internal OD4session
        cluon::OD4Session internal(INTERNAL_CHANNEL, [](cluon::data::Envelope && envelope) noexcept {});

        // In case, nither OD4Session is not working
        if (od4.isRunning() == 0) {
            cout << "ERROR: No od4 session is running!!!" << endl;
            return -1;
        }
            
         else if (internal.isRunning() == 0){
            cout << "ERROR: No internal session is running!!!" << endl;
            return -1;

         }else{
            // Specify the messages as in messages.odvd
            opendlv::proxy::GroundSteeringReading msgSteering;
            opendlv::proxy::PedalPositionReading msgPedal;
                
            // HANDELING MOVMENTS: forward sending the commands received, via the commands OD4Session then to the web-visualizaation internal OD4session
            cout << " EXECUTING SOME MOVEMENTS ..." << endl;
            msgSteering.steeringAngle(anglef);
            od4.send(msgSteering);
            internal.send(msgSteering);
            
            msgPedal.percent(speedf);
            od4.send(msgPedal);
            internal.send(msgPedal);
            // A delay for the messages' thread
            this_thread::sleep_for(chrono::milliseconds(delay));
            }
        }
    }
}

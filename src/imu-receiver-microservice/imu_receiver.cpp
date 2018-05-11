/*
 * Copyright (C) 2018 DIT168 - Group 13
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Created by Rema Salman
 * Edited by Laiz Figueroa -> OD4Sessions for internal communications
 *
 * References used : - The UDP server is, available on: <https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html>
 */

/* libraries used for the UDP implementation */
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <thread>

/* Cloun library for the commands' communication */
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

/* Variables' declarations */
using namespace std; // Name space declaration

// CIDs of Cloun (od4sessions) chancels deceleration
static const int IMU_CHANNEL            = 249;
static const int INTERNAL_CHANNEL       = 240;
// Delay for sending the messages through the od4 sessions
const int delay = 100;

int SOCKET_BUFFER_SIZE = 1024;
socklen_t *addrlen;
float imu_value;

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
    // Defining socket's IP address (listens to any income data from whateverport)
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    // Defining the port used for transporting the data
    server_addr.sin_port = htons(50002);
    //binding a unique name to the descriptor socket
    bind(server, (sockaddr * ) & server_addr, size);
    // buffer's deceleration
    char buffer[SOCKET_BUFFER_SIZE];
    
    /**
     * The loop continuously listening to data from the client IMU
     */
    while (1) {
        size_t array = sizeof(buffer);
        cout << "\n Clearing buffer before receving ... " << endl;
        // cleaning the buffer
        memset(buffer, 0, sizeof(buffer));
        // receive function for any incoming datagram, via the specified IP/Port
        recvfrom(server, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &size);
        
        /* Side case failure of receiving */
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
        
        /*
         * OD4Session to send to the internal channel -> One responsible to display on the webview.
         */
        
        cluon::OD4Session internal(INTERNAL_CHANNEL, {});
        
        /*
         * OD4Session to send the accelerometer data to V2V.
         */
        cluon::OD4Session imuSender(IMU_CHANNEL, {});
        
        /* In case, neither OD4Session is not working */
        if (imuSender.isRunning() == 0) {
            cout << "ERROR: No imuSender session is running!!!" << endl;
            return -1;
        }
        
        else if (internal.isRunning() == 0){
            cout << "ERROR: No internal session is running!!!" << endl;
            return -1;
            
        }else{
            ImuData id;
            id.accel_y(imu_value);
            id.accel_x(0.0);
            id.accel_z(0.0);
            
            // send the imu data to V2V
            imuSender.send(id);
            // Send the imu data to the web-view
            internal.send(id);
            // A delay for the messages' thread
            this_thread::sleep_for(chrono::milliseconds(delay));
            
        }
    }
}

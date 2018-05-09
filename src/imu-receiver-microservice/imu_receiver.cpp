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
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <thread>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"


static const int IMU_CHANNEL            = 249;
static const int INTERNAL_CHANNEL       = 240;

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
        
        /*
        * OD4Session to send to the internal channel -> One responsible to display on the webview.
        */
        
        cluon::OD4Session internal(INTERNAL_CHANNEL, [](cluon::data::Envelope &&envelope) noexcept {});
        
        /*
        * OD4Session to send the accelometer data to V2V. 
        */
        cluon::OD4Session imuSender(IMU_CHANNEL,
                              [](cluon::data::Envelope &&envelope) noexcept {});

        ImuData id;
        id.accel_y(imu_value);
        id.accel_x(0.0);
        id.accel_z(0.0);
        /*
        * send the imu data to V2V
        */
        imuSender.send(id);
        /*
        * Send the imu data to the webview
        */
        internal.send(id);
        

    }
}

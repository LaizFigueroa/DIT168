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
//  Created by Laiz Figueroa on 2018-04-28.
//  Edited by Rema Salman -> Added UDP Sender
//  IMU code is based on: <http://www.strawsondesign.com/#!manual-imu>.

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

extern "C"{
#include <roboticscape.h>
}

float accel_y;
using namespace std;
int SOCKET_BUFFER_SIZE = 1024;
socklen_t *addrlen; 

int main() {
    sockaddr_in client_addr;
    int client;
    socklen_t size = sizeof(client_addr);
    client = socket(AF_INET, SOCK_DGRAM, 0);


    rc_initialize();
    rc_set_state(RUNNING);

    while (rc_get_state() == RUNNING) {
        if (rc_is_gyro_calibrated() != 1){ // Check gyroscope calibration befor$
            std::cout << "WARNING: Gyroscope is not calibrated" << std::endl;
        }
        else {

            rc_imu_config_t conf = rc_default_imu_config(); // Setting the defa$
            rc_imu_data_t imu_data; // Get the data from the imu using the libr$
            if (rc_initialize_imu(&imu_data, conf) != 0){ // Initialize imu
                std::cout << "ERROR: Initialization failed" << std::endl;
                return -1;
            }
        else{

                 if(rc_read_accel_data(&imu_data) != 0){// Check the accelomete$
                    std::cout << "ERROR: Accelometer read failed" << std::endl;
                }
                else{
                   accel_y = imu_data.accel[1]; // Store Y values in a local v$

                    std::cout << "Accelerometer values" << std::endl; // Print $
                    printf("%6.2f\n", accel_y);

                        if(accel_y <= 0.34 & accel_y > 0.00){
                        accel_y = 0.00;
                        std::cout << "Clean accelerometer values" << std::endl; // Print the value stored as r$
                        printf("%6.2f\n", accel_y);

                        }
                         /*************************************                $
                        *          SERVER (SENDING)         *
                         *                                   *
                         *************************************/

                        if (client == -1) {
                            cout << "\n Error establishing socket..." << endl;
                            exit(1);
                        }

                        cout << "\n=> Socket server has been created..." << endl;
                        client_addr.sin_family = AF_INET;
                        client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
                        client_addr.sin_port = htons(50002);


                        /**
                         * this while loop continously sending data to the port
                         */
                            int returnvalue=0;
                            char buffer[SOCKET_BUFFER_SIZE];
                            size_t pos = 0  ;      
                        size_t array = sizeof(buffer);
                        cout << "before  ..." << endl;

                               memset(buffer, 0, sizeof(buffer));
                                sprintf (buffer, "%6.2f", accel_y);

 //checking the sent values
            if (sendto(client, &buffer, sizeof(buffer), 0, (struct sockaddr*) &client_addr, sizeof(sockaddr))== -1){
                cout << "Sending failed" << endl;
                break;

            }else{


 // CONVERTING the float into a char
                            sprintf (buffer, "%6.2f", accel_y);
                            cout << "Sending success" << endl;
}
                // CONVERTING the f
        #define closesocket(client)
        closesocket(client);
        cout << "Closing the socket" << endl;
                      }
                                 }
        }
}
    rc_power_off_imu(); // To stop the IMU cleanly and put it into a low power $
    int rc_cleanup(); // Undo everything done by initialize cape
    fflush(stdout);
    return 0;
}










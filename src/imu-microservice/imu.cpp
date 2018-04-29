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
//  IMU code is based on: <http://www.strawsondesign.com/#!manual-imu>.


#include "imu.hpp"

int main(){
    rc_initialize();
    rc_set_state(RUNNING);
    
    while (rc_get_state() == RUNNING) {
        if (rc_is_gyro_calibrated() != 1){ // Check gyroscope calibration before starting to use the API
            std::cout << "WARNING: Gyroscope is not calibrated" << std::endl;
        }
        else {
        
            rc_imu_config_t new_config = rc_get_default_imu_config(); // Setting the default configuration for the imu
            rc_imu_data_t imu_data; // Get the data from the imu using the library structure
            
            if (rc_initialize_imu(&imu_data, new_config) != 0){ // Initialize imu
                std::cout << "ERROR: Initialization failed" << std::endl;
                return -1;
            }
            else {
                if(rc_read_accel_data(&imu_data) != 0){// Check the accelometer data
                    std::cout << "ERROR: Accelometer read failed" << std::endl;
                }
                else{
                    accel_y = imu_data.accel[1]; // Store Y values in a local variable
                    
                    std::cout << "Accelerometer values" << std::endl; // Print the value stored as received
                    printf("%6.2f\n", accel_y);
                    
                }
            }
        }
    }
    rc_power_off_imu(); // To stop the IMU cleanly and put it into a low power state
    rc_cleanup(); // Undo everything done by initialize cape
    fflush(stdout);
    return 0;
}


///**
//* Implementation of the Imu class declared in imu.hpp
//*/
//Imu::Imu() {
//
//cluon::OD4Session od3(224, {});
//    internal =
//    std::make_shared<cluon::OD4Session>(INTERNAL_CHANNEL, [this](cluon::data::Envelope &&envelope) noexcept {});
//
//    imu =
//    std::make_shared<cluon::OD4Session>(IMU_CHANNEL, [this](cluon::data::Envelope &&envelope) noexcept {});
//
//}
//
//    void Imu::sendAcceleration() {
//        if (!followerIp.empty()) return;
//        ImuData imuData;
//        imuData.accel();
//        imuData.gyro();
//        internal->send(imuData);
//    }
//
//    GetAceleration acceleration = cluon::extractMessage<ImuData>(std::move(envelope));
//    std::cout << "received 'IMU acceleration' : '" << acceleration.accel() << "received 'IMU gyroscope' : '" << acceleration.gyro() << "'." << std::endl;
//
//    internal->send(acceleration);
//
//
//    if(accel_y<0.5 && accel_y>0.1) // Cleaning the values to 0
//        accel_y = 0.0;
//
//    std::cout << "Data cleaned" << std::endl;
//    std::cout << accel_y << std::endl;


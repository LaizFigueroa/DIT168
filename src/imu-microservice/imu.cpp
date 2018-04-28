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

#include "imu.hpp"

int main(){
    
    internal =
    std::make_shared<cluon::OD4Session>(INTERNAL_CHANNEL, [this](cluon::data::Envelope &&envelope) noexcept {});
    
    imu =
    std::make_shared<cluon::OD4Session>(IMU_CHANNEL, [this](cluon::data::Envelope &&envelope) noexcept {});
    
    
    
    
    
    GetAceleration acceleration = cluon::extractMessage<ImuData>(std::move(envelope));
    std::cout << "received 'IMU acceleration' : '" << acceleration.accel() << "received 'IMU gyroscope' : '" << acceleration.gyro() << "'." << std::endl;
    
    internal->send(acceleration);
    
    typedef enum rc_accel_fsr_t {
        A_FSR_2G,
        A_FSR_4G,
        A_FSR_8G,
        A_FSR_16G
    } rc_accel_fsr_t;
    
    typedef struct rc_imu_config_t{
        // full scale ranges for sensors
        rc_accel_fsr_t accel_fsr; // AFS_2G, AFS_4G, AFS_8G, AFS_16G
        rc_gyro_fsr_t gyro_fsr;  // GFS_250,GFS_500,GFS_1000,GFS_2000
        
        // internal low pass filter constants
        rc_gyro_dlpf_t gyro_dlpf;
        rc_accel_dlpf_t accel_dlpf;
        
        // magnetometer use is optional
        int enable_magnetometer; // 0 or 1
        
        // DMP settings, only used with DMP interrupt
        int dmp_sample_rate;
        rc_imu_orientation_t orientation; //orientation matrix
        // higher mix_factor means less weight the compass has on fused_TaitBryan
        float compass_time_constant;     // time constant for filtering fused yaw
        int dmp_interrupt_priority; // scheduler priority for handler
        int show_warnings;    // set to 1 to enable showing of rc_i2c_bus warnings
        
    } rc_imu_config_t;
    
    typedef struct rc_imu_data_t{
        // last read sensor values in real units
        float accel[3];    // units of m/s^2
        float gyro[3];    // units of degrees/s
        float mag[3];    // units of uT
        float temp;        // units of degrees Celsius
        
        // 16 bit raw adc readings from each sensor
        int16_t raw_gyro[3];
        int16_t raw_accel[3];
        
        // FSR-derived conversion ratios from raw to real units
        float accel_to_ms2;    // to m/s^2
        float gyro_to_degs;    // to degrees/s
        
        // everything below this line is available in DMP mode only
        // quaternion and TaitBryan angles from DMP based on ONLY Accel/Gyro
        float dmp_quat[4];        // normalized quaternion
        float dmp_TaitBryan[3];    // radians pitch/roll/yaw X/Y/Z
        
        // If magnetometer is enabled in DMP mode, the following quaternion and
        // TaitBryan angles will be available which add magnetometer data to filter
        float fused_quat[4];        // normalized quaternion
        float fused_TaitBryan[3];    // radians pitch/roll/yaw X/Y/Z
        float compass_heading;        // heading filtered with gyro and accel data
        float compass_heading_raw;    // heading in radians from magnetometer
    } rc_imu_data_t;
    
    // mpu.calibratedMag[VEC3_X],
    // mpu.calibratedMag[VEC3_Y],
    // mpu.calibratedMag[VEC3_Z]);
    // printf("W: %0.2f X: %0.2f Y: %0.2f Z: %0.2f ",
    // mpu.fusedQuat[QUAT_W],
    // mpu.fusedQuat[QUAT_X],
    // mpu.fusedQuat[QUAT_Y],
    // mpu.fusedQuat[QUAT_Z]);
    fflush(stdout);
}
return 0; }

    
    rc_power_off_imu();
    rc_cleanup();
    return 0;
}

rc_imu_config_t rc_get_default_imu_config();
int rc_set_imu_config_to_defaults(rc_imu_config_t *conf);

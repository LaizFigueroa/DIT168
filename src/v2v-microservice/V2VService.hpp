/* Copyright (C) 2018 DIT168 - Group 13
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
* Created by V2V representatives
* Edited by Laiz Figueroa -> OD4Session for internal and Imu communication.
*/


#ifndef V2V_PROTOCOL_DEMO_V2VSERVICE_H
#define V2V_PROTOCOL_DEMO_V2VSERVICE_H

#include <iomanip>
#include <unistd.h>
#include <sys/time.h>
#include "cluon/OD4Session.hpp"
#include "cluon/UDPSender.hpp"
#include "cluon/UDPReceiver.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <thread>

#include "cluon-complete.hpp"

/** ADD YOUR CAR_IP AND GROUP_ID HERE:  *****************/

static std::string CAR_IP;
static const std::string YOUR_GROUP_ID  = "13";

/********************************************************/
/** DON'T CHANGE STUFF BELOW THIS LINE. *****************/
/********************************************************/

static const int BROADCAST_CHANNEL 	= 250;
static const int DEFAULT_PORT 		= 50001;

static const int ANNOUNCE_PRESENCE	= 1001;
static const int FOLLOW_REQUEST 	= 1002;
static const int FOLLOW_RESPONSE 	= 1003;
static const int STOP_FOLLOW 		= 1004;
static const int LEADER_STATUS 		= 2001;
static const int FOLLOWER_STATUS 	= 3001;

/********************************************************/
/** INTERNAL COMMUNICATIONS *****************************/
/********************************************************/

static const int INTERNAL_CHANNEL	= 240;
static const int IMU_CHANNEL	    = 249;

static const int PEDAL_POSITION		= 1041;
static const int GROUND_STEERING	= 1045;


class V2VService {
public:
    std::map <std::string, std::string> presentCars;

    V2VService();

    void announcePresence();
    void followRequest(std::string vehicleIp);
    void followResponse();
    void stopFollow(std::string vehicleIp);
    void leaderStatus(float speed, float steeringAngle, uint8_t distanceTraveled);
    void followerStatus();

private:
    std::string leaderIp;
    std::string followerIp;

    std::shared_ptr<cluon::OD4Session>  broadcast;
    std::shared_ptr<cluon::OD4Session>  internal;
    std::shared_ptr<cluon::OD4Session>  imu;
    std::shared_ptr<cluon::UDPReceiver> incoming;
    std::shared_ptr<cluon::UDPSender>   toLeader;
    std::shared_ptr<cluon::UDPSender>   toFollower;

    static uint32_t getTime();
    static std::pair<int16_t, std::string> extract(std::string data);
    template <class T>
    static std::string encode(T msg);
    template <class T>
    static T decode(std::string data);
};

#endif //V2V_PROTOCOL_DEMO_V2VSERVICE_H

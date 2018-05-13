#include "V2VService.hpp"

cluon::OD4Session od3(242, {});

int main(int argc, char **argv) {
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();

    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);

    if (0 == commandlineArguments.count("ip") && 0 == commandlineArguments.count("limit") && commandlineArguments.count("skip") == 0
        && commandlineArguments.count("angle") == 0 && commandlineArguments.count("delay") == 0) {

        std::cout << "Please enter correct parameters " << std::endl;

    } else {
        CAR_IP = (commandlineArguments["ip"]);
        lim = std::stoi(commandlineArguments["limit"]);
        skip = std::stoi(commandlineArguments["skeep"]);
        angle = std::stoi(commandlineArguments["angle"]);
        del = std::stoi(commandlineArguments["delay"]);
        acc = std::stof(commandlineArguments["speed"]);
    }
    std::cout << "IP set to:" << CAR_IP << std::endl;

    float angle = 0;
    float speed = 0;
    while (1) {
        int choice;
        std::string groupId;
        std::cout << "Which message would you like to send?" << std::endl;
        std::cout << "(1) AnnouncePresence" << std::endl;
        std::cout << "(2) FollowRequest" << std::endl;
        std::cout << "(3) FollowResponse" << std::endl;
        std::cout << "(4) StopFollow" << std::endl;
        std::cout << "(5) LeaderStatus" << std::endl;
        std::cout << "(6) FollowerStatus" << std::endl;
        std::cout << "(#) Nothing, just quit." << std::endl;
        std::cout << ">> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                v2vService->announcePresence();
                break;
            case 2: {
                std::cout << "Which group do you want to follow?" << std::endl;
                std::cin >> groupId;
                if (v2vService->presentCars.find(groupId) != v2vService->presentCars.end())
                    v2vService->followRequest(v2vService->presentCars[groupId]);
                else std::cout << "Sorry, unable to locate that groups vehicle!" << std::endl;
                break;
            }
            case 3:
                v2vService->followResponse();
                break;
            case 4: {
                std::cout << "Which group do you want to stop follow?" << std::endl;
                std::cin >> groupId;
                if (v2vService->presentCars.find(groupId) != v2vService->presentCars.end())
                    v2vService->stopFollow(v2vService->presentCars[groupId]);
                else std::cout << "Sorry, unable to locate that groups vehicle!" << std::endl;
                break;
            }
            case 5:
                while (1) {

                    cluon::OD4Session od4(242, [&angle, &speed](cluon::data::Envelope &&envelope) noexcept {

                        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
                            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(
                                    std::move(envelope));
                            std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "."
                                      << std::endl;
                            std::cout << "setting angle..." << std::endl;
                            angle = receivedMsg.steeringAngle();
                            std::cout << "set angle!" << std::endl;
                        }
                        if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
                            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(
                                    std::move(envelope));
                            std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "."
                                      << std::endl;

                            std::cout << "setting speed..." << std::endl;
                            speed = receivedMsg.percent();
                            std::cout << "set speed!" << std::endl;
                        }
                        std::cout << "assigning vars for send..." << std::endl;

                    });
                    v2vService->leaderStatus(speed, angle, 100);

                }
                break;
            case 6:
                v2vService->followerStatus();
                break;
            default:
                exit(0);
        }
    }
}

/**
 * Implementation of the V2VService class as declared in V2VService.hpp
 */
V2VService::V2VService() {

    /*
     * The broadcast field contains a reference to the broadcast channel which is an OD4Session. This is where
     * AnnouncePresence messages will be received.
     */
    broadcast =
            std::make_shared<cluon::OD4Session>(BROADCAST_CHANNEL,
                                                [this](cluon::data::Envelope &&envelope) noexcept {
                                                    std::cout << "[OD4] ";
                                                    switch (envelope.dataType()) {
                                                        case ANNOUNCE_PRESENCE: {
                                                            AnnouncePresence ap = cluon::extractMessage<AnnouncePresence>(
                                                                    std::move(envelope));
                                                            std::cout << "received 'AnnouncePresence' from '"
                                                                      << ap.vehicleIp() << "', GroupID '"
                                                                      << ap.groupId() << "'!" << std::endl;

                                                            presentCars[ap.groupId()] = ap.vehicleIp();
                                                            internal->send(ap);
                                                            break;
                                                        }
                                                        default:
                                                            std::cout << "¯\\_(ツ)_/¯" << std::endl;
                                                    }
                                                });

    /*
    * OD4Session Channel to send all the data exchanged on V2V and internally (differents CIDs) to one CID (240) and then be used
    * by the webview.
    */
    internal =
            std::make_shared<cluon::OD4Session>(INTERNAL_CHANNEL, [this](cluon::data::Envelope &&envelope) noexcept {});

    /*
    * OD4Session Channel to receive accelometer data (accel_y) from the car to be used for the next step of development.
    */
    imu =
            std::make_shared<cluon::OD4Session>(IMU_CHANNEL, [this](cluon::data::Envelope &&envelope) noexcept {
//            if (envelope.dataType() == 1412) {
                //              ImuData accel = cluon::extractMessage<ImuData>(std::move(envelope));
//
                //              std::cout << "Received 'ImuData': Accel_x-> '"
                //                            << accel.accel_x() << "', Accel_y-> '"
                //                          << accel.accel_y() << "', Accel_z-> '"
                //                        << accel.accel_z() << "'. " << std::endl;}
            });
    /*
     * Each car declares an incoming UDPReceiver for messages directed at them specifically. This is where messages
     * such as FollowRequest, FollowResponse, StopFollow, etc. are received.
     */
    incoming =
            std::make_shared<cluon::UDPReceiver>("0.0.0.0", DEFAULT_PORT,
                                                 [this](std::string &&data, std::string &&sender,
                                                        std::chrono::system_clock::time_point &&ts) noexcept {
                                                     std::cout << "[UDP] ";
                                                     std::pair<int16_t, std::string> msg = extract(data);

                                                     switch (msg.first) {
                                                         case FOLLOW_REQUEST: {
                                                             FollowRequest followRequest = decode<FollowRequest>(
                                                                     msg.second);
                                                             std::cout << "received '" << followRequest.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;

                                                             // After receiving a FollowRequest, check first if there is currently no car already following.
                                                             if (followerIp.empty()) {
                                                                 unsigned long len = sender.find(
                                                                         ':');    // If no, add the requester to known follower slot
                                                                 followerIp = sender.substr(0,
                                                                                            len);      // and establish a sending channel.
                                                                 toFollower = std::make_shared<cluon::UDPSender>(
                                                                         followerIp, DEFAULT_PORT);
                                                                 internal->send(followRequest);
                                                                 followResponse();
                                                             }
                                                             break;
                                                         }
                                                         case FOLLOW_RESPONSE: {
                                                             FollowResponse followResponse = decode<FollowResponse>(
                                                                     msg.second);
                                                             std::cout << "received '" << followResponse.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;
                                                             internal->send(followResponse);
                                                             break;
                                                         }
                                                         case STOP_FOLLOW: {
                                                             StopFollow stopFollow = decode<StopFollow>(msg.second);
                                                             std::cout << "received '" << stopFollow.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;

                                                             // Clear either follower or leader slot, depending on current role.
                                                             unsigned long len = sender.find(':');
                                                             if (sender.substr(0, len) == followerIp) {
                                                                 followerIp = "";
                                                                 toFollower.reset();
                                                             } else if (sender.substr(0, len) == leaderIp) {
                                                                 leaderIp = "";
                                                                 toLeader.reset();
                                                             }
                                                             internal->send(stopFollow);
                                                             break;
                                                         }
                                                         case LEADER_STATUS: {

                                                             LeaderStatus leaderStatus = decode<LeaderStatus>(
                                                                     msg.second);
                                                             std::cout << " Received '" << leaderStatus.LongName()
                                                                       << "' from '" << sender << "'!" << std::endl;
                                                             if (leaderStatus.steeringAngle() != 0 &&
                                                                 leaderStatus.speed() != 0) {
                                                                 std::cout << " Leader's steeringAngle: "
                                                                           << leaderStatus.steeringAngle() << std::endl;
                                                                 std::cout << "Leader's speed: " << leaderStatus.speed()
                                                                           << std::endl;
                                                                 std::cout << "Distance traveled"
                                                                           << leaderStatus.distanceTraveled() << "'!"
                                                                           << std::endl;
                                                                 std::cout << "Distance traveled"
                                                                           << leaderStatus.timestamp() << "'!"
                                                                           << std::endl;
                                                             }
                                                             w++;
                                                             if (w >= del) {
                                                                 std::queue<int64_t> empty;
                                                                 std::swap(timestamp, empty);
                                                                 w = 0;
                                                             }

                                                             internal->send(leaderStatus);
                                                             std::cout << "sent internal" << std::endl;

                                                             /**
                                                             * The follower car mock the leaders movement if and only if either its steering angle or pedal position is
                                                             * equal to 0. The moment the leader starts to turn with a given speed different to zero the follower will keep going forward
                                                             * for a specific time. Meanwhile the values of the pedal and steering of the leader will be stored in a queue and they will
                                                             * sent to the follower when the pre-set time expires
                                                             **/
                                                             opendlv::proxy::GroundSteeringReading followerAngle;
                                                             opendlv::proxy::PedalPositionReading followerSpeed;

                                                             if (follower) {

                                                                 float steer = leaderStatus.steeringAngle();
                                                                 float run = leaderStatus.speed();

                                                                 if (steer != 0 && run != 0) {
                                                                     std::cout << "inside if " << std::endl;
                                                                     if (timestamp.empty()) {
                                                                         cluon::data::TimeStamp start = cluon::time::now();
                                                                         timestamp.push(
                                                                                 cluon::time::toMicroseconds(start) /
                                                                                 100000);
                                                                         std::cout << " val and val /100000  "
                                                                                   << cluon::time::toMicroseconds(start)
                                                                                   << "//"
                                                                                   <<
                                                                                   cluon::time::toMicroseconds(start) /
                                                                                   100000 << std::endl;
                                                                     }

                                                                     p.pedal = leaderStatus.speed();
                                                                     p.steer = leaderStatus.steeringAngle();

                                                                     values.push(p);
                                                                     std::cout << "stored in values " << p.pedal
                                                                               << "///" << p.steer << std::endl;
                                                                     leaderstamp.push_front(leaderStatus.timestamp());
                                                                 }
                                                                 if (!timestamp.empty()) {
                                                                     cluon::data::TimeStamp start = cluon::time::now();
                                                                     timestamp.push(cluon::time::toMicroseconds(start) /
                                                                                    100000);
                                                                     std::cout << " val2 and val2 /100000  "
                                                                               << cluon::time::toMicroseconds(start)
                                                                               << "//"
                                                                               << cluon::time::toMicroseconds(start) /
                                                                                  100000
                                                                               << std::endl;
                                                                 }

                                                                 if (timestamp.size() > 1) {

                                                                      val = timestamp.back() - timestamp.front();

                                                                     if (val > lim && values.size() > skip) {

                                                                         std::cout << "inside second if val is  " << val
                                                                                   << std::endl;

                                                                         first = values.front();
                                                                         followerAngle.steeringAngle(first.steer);
                                                                         followerSpeed.percent(first.pedal);
                                                                         values.pop();
                                                                         flush = 1;
                                                                         std::cout << "flush at first is " << flush
                                                                                   << std::endl;
                                                                     } else {
                                                                         followerAngle.steeringAngle(0);
                                                                         followerSpeed.percent(leaderStatus.speed());

                                                                         std::cout << "flush at second is " << flush
                                                                                   << std::endl;
                                                                         if (flush == 1) {
                                                                             std::queue<int64_t> empty;
                                                                             std::swap(timestamp, empty);

                                                                         }

                                                                     }

                                                                 } else {
                                                                     followerAngle.steeringAngle(
                                                                             leaderStatus.steeringAngle());
                                                                     followerSpeed.percent(leaderStatus.speed());

                                                                 }

                                                                 od3.send(followerAngle);
                                                                 od3.send(followerSpeed);
                                                             }
                                                             break;
                                                         }
                                                         default:
                                                             std::cout << "¯\\_(ツ)_/¯" << std::endl;
                                                     }
                                                 });
}

/**
 * This function sends an AnnouncePresence (id = 1001) message on the broadcast channel. It will contain information
 * about the sending vehicle, including: IP, port and the group identifier.
 */
void V2VService::announcePresence() {
    if (!followerIp.empty()) return;
    AnnouncePresence announcePresence;
    announcePresence.vehicleIp(CAR_IP);
    announcePresence.groupId(YOUR_GROUP_ID);
    broadcast->send(announcePresence);
}

/**
 * This function sends a FollowRequest (id = 1002) message to the IP address specified by the parameter vehicleIp. And
 * sets the current leaderIp field of the sending vehicle to that of the target of the request.
 *
 * @param vehicleIp - IP of the target for the FollowRequest
 */
void V2VService::followRequest(std::string vehicleIp) {
    if (!leaderIp.empty()) return;
    leaderIp = vehicleIp;
    toLeader = std::make_shared<cluon::UDPSender>(leaderIp, DEFAULT_PORT);
    FollowRequest followRequest;
    toLeader->send(encode(followRequest));
}

/**
 * This function send a FollowResponse (id = 1003) message and is sent in response to a FollowRequest (id = 1002).
 * This message will contain the NTP server IP for time synchronization between the target and the sender.
 */
void V2VService::followResponse() {
    if (followerIp.empty()) return;
    FollowResponse followResponse;
    toFollower->send(encode(followResponse));
}

/**
 * This function sends a StopFollow (id = 1004) request on the ip address of the parameter vehicleIp. If the IP address is neither
 * that of the follower nor the leader, this function ends without sending the request message.
 *
 * @param vehicleIp - IP of the target for the request
 */
void V2VService::stopFollow(std::string vehicleIp) {
    StopFollow stopFollow;
    if (vehicleIp == leaderIp) {
        toLeader->send(encode(stopFollow));
        leaderIp = "";
        toLeader.reset();
    }
    if (vehicleIp == followerIp) {
        toFollower->send(encode(stopFollow));
        followerIp = "";
        toFollower.reset();
    }
}

/**
 * This function sends a FollowerStatus (id = 3001) message on the leader channel.
 *
 * @param speed - current velocity
 * @param steeringAngle - current steering angle
 * @param distanceFront - distance to nearest object in front of the car sending the status message
 * @param distanceTraveled - distance traveled since last reading
 */
void V2VService::followerStatus() {
    if (leaderIp.empty()) return;
    FollowerStatus followerStatus;
    toLeader->send(encode(followerStatus));
}

/**
 * This function sends a LeaderStatus (id = 2001) message on the follower channel.
 *
 * @param speed - current velocity
 * @param steeringAngle - current steering angle
 * @param distanceTraveled - distance traveled since last reading
 */
void V2VService::leaderStatus(float speed, float steeringAngle, uint8_t distanceTraveled) {
    if (followerIp.empty()) return;
    LeaderStatus leaderStatus;
    leaderStatus.timestamp(getTime());
    leaderStatus.speed(speed);
    leaderStatus.steeringAngle(steeringAngle);
    leaderStatus.distanceTraveled(distanceTraveled);
    toFollower->send(encode(leaderStatus));
}

/**
 * Gets the current time.
 *
 * @return current time in milliseconds
 */
uint32_t V2VService::getTime() {
    timeval now;
    gettimeofday(&now, nullptr);
    return (uint32_t) now.tv_usec / 1000;
}

/**
 * The extraction function is used to extract the message ID and message data into a pair.
 *
 * @param data - message data to extract header and data from
 * @return pair consisting of the message ID (extracted from the header) and the message data
 */
std::pair<int16_t, std::string> V2VService::extract(std::string data) {
    if (data.length() < 10) return std::pair<int16_t, std::string>(-1, "");
    int id, len;
    std::stringstream ssId(data.substr(0, 4));
    std::stringstream ssLen(data.substr(4, 10));
    ssId >> std::hex >> id;
    ssLen >> std::hex >> len;
    return std::pair<int16_t, std::string>(
            data.length() - 10 == len ? id : -1,
            data.substr(10, data.length() - 10)
    );
};

/**
 * Generic encode function used to encode a message before it is sent.
 *
 * @tparam T - generic message type
 * @param msg - message to encode
 * @return encoded message
 */
template<class T>
std::string V2VService::encode(T msg) {
    cluon::ToProtoVisitor v;
    msg.accept(v);
    std::stringstream buff;
    buff << std::hex << std::setfill('0')
         << std::setw(4) << msg.ID()
         << std::setw(6) << v.encodedData().length()
         << v.encodedData();
    return buff.str();
}

/**
 * Generic decode function used to decode an incoming message.
 *
 * @tparam T - generic message type
 * @param data - encoded message data
 * @return decoded message
 */
template<class T>
T V2VService::decode(std::string data) {
    std::stringstream buff(data);
    cluon::FromProtoVisitor v;
    v.decodeFrom(buff);
    T tmp = T();
    tmp.accept(v);
    return tmp;
}

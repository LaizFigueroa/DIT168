#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"

#include "messages.hpp"


int main() {
    std::cout << "Interceptor online..." << std::endl;
    std::cout << "Receiving at CID of 224, sending to 111, sensor connected to 112" << std::endl;
   
	cluon::OD4Session od3{111};
	float steer;
	float pedal;
 	float limit=0.1;
	float pedalNeutral = 0;
	opendlv::proxy::PedalPositionReading p1;
	opendlv::proxy::GroundSteeringReading s1;
     	float sens;

 cluon::OD4Session od5(112,[&sens](cluon::data::Envelope &&envelope) noexcept {
          
        if (envelope.dataType() == opendlv::proxy::DistanceReading::ID()) {
            opendlv::proxy::DistanceReading receivedMsg = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            std::cout << "Sensor reading: " << receivedMsg.distance() << "." << std::endl;
            sens=(receivedMsg.distance());
        }
    });

while(1){

                      cluon::OD4Session od4(224,[&steer,&pedal](cluon::data::Envelope &&envelope) noexcept {

                           if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
                               opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
                               std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
				steer=receivedMsg.steeringAngle();

                           }
                           else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
                               opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
                               std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
				pedal=receivedMsg.percent();
                           }



                       });

std::cout << "Pre-IF steer: "<< steer  << " Pre-IF pedal: "<< pedal << "Sensor check: " << sens<< std::endl;

if ((sens<limit) && (pedal > pedalNeutral)){

        p1.percent(0);
 
        od3.send(p1);
        s1.steeringAngle(steer);
std::this_thread::sleep_for(std::chrono::milliseconds(2));
std::cout << "Sent angle:"<< s1.steeringAngle()  << " Sent zero:"<< p1.percent()<< std::endl;
        od3.send(s1);
} else {
        p1.percent(pedal);

        od3.send(p1);
        s1.steeringAngle(steer);
std::this_thread::sleep_for(std::chrono::milliseconds(2));
std::cout << "Sent angle:" <<s1.steeringAngle() << " Sent pedal "<< p1.percent() << std::endl;
        od3.send(s1);
}

	//s1.steeringAngle(steer);
        //od3.send(s1);

}
    return 0;
}




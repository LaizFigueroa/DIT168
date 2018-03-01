#include <iostream>
#include <chrono>

#include "cluon/UDPSender.hpp"
#include "cluon/UDPReceiver.hpp"

int main(int /*argc*/, char** /*argv*/) {

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(5s);
    //std::cout << "Operational " << std::endl;

cluon::UDPReceiver receiver("255.0.0.111", 1236,
        [](std::string &&data, std::string &&/*from*/,
           std::chrono::system_clock::time_point &&/*timepoint*/) 

noexcept {
        std::cout << "Received " << data.size() << " bytes." << std::endl;
	 std::cout << "Received " <<  data << std::endl;
    });


	cluon::UDPSender sender{"255.0.0.111", 1236};
    sender.send("Testing");


    using namespace std::literals::chrono_literals;

    while (receiver.isRunning()) {

        std::this_thread::sleep_for(1s);

    }

    return 0;

}

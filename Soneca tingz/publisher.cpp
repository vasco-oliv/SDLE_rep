#include <zmq.hpp>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    zmq::context_t context(1);

    // Create a PUB socket and connect to the proxy's XPUB interface
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.connect("tcp://localhost:6667");  // Connect to the proxy

    // Simulate sending messages every second
    int count = 0;
    while (true) {
        std::string message = "Hello " + std::to_string(count);
        zmq::message_t zmq_message(message.c_str(), message.size());

        std::cout << "Publishing: " << message << std::endl;
        publisher.send(zmq_message, zmq::send_flags::none);

        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++count;
    }

    return 0;
}

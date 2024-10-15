#include <zmq.hpp>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");

    // Allow some time for the subscriber to connect
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int temperature = 20; // Starting temperature
    while (true) {
        std::string message = "10001 " + std::to_string(temperature++);
        zmq::message_t msg(message.size());
        memcpy(msg.data(), message.c_str(), message.size());
        publisher.send(msg, zmq::send_flags::none);
        std::cout << "Published: " << message << std::endl;

        // Simulate some time between updates
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
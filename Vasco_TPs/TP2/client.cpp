#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

int main (int argc, char *argv[]) {
    zmq::context_t context(1);

    // Connect to task ventilator
    zmq::socket_t receiver(context, ZMQ_PULL);
    try {
        receiver.connect("tcp://localhost:5557");
    } catch (const zmq::error_t& e) {
        std::cerr << "Error connecting to task ventilator: " << e.what() << std::endl;
        return -1;
    }

    // Connect to weather server
    zmq::socket_t subscriber(context, ZMQ_SUB);
    try {
        subscriber.connect("tcp://localhost:5556");
    } catch (const zmq::error_t& e) {
        std::cerr << "Error connecting to weather server: " << e.what() << std::endl;
        return -1;
    }
    
    const std::string subscription = "10001"; // Make sure there's no trailing space
    subscriber.set(zmq::sockopt::subscribe, subscription);

    // Allow some time for connections
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Initialize poll set
    zmq::pollitem_t items[] = {
        { receiver, 0, ZMQ_POLLIN, 0 },
        { subscriber, 0, ZMQ_POLLIN, 0 }
    };

    // Process messages from both sockets
    while (true) {
        zmq::message_t message;
        zmq::poll(&items[0], 2, -1);

        if (items[0].revents & ZMQ_POLLIN) {
            try {
                receiver.recv(&message);
                std::string received_message(static_cast<char*>(message.data()), message.size());
                std::cout << "Received from 0: " << received_message << std::endl;

            } catch (const zmq::error_t& e) {
                std::cerr << "Receive error from receiver: " << e.what() << std::endl;
            }
        }
        if (items[1].revents & ZMQ_POLLIN) {
            try {
                subscriber.recv(&message);
                std::string received_message(static_cast<char*>(message.data()), message.size());
                std::cout << "Received from 1: " << received_message << std::endl;
            } catch (const zmq::error_t& e) {
                std::cerr << "Receive error from subscriber: " << e.what() << std::endl;
            }
        }
    }
    return 0;
}

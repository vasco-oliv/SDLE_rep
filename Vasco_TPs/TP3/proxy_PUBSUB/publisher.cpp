// publisher.cpp
#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main() {
    zmq::context_t context(1);

    // Create a publisher socket
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5555"); // Connect to proxy XSUB

    std::cout << "Publisher started\n";

    int topic_number = 1;
    while (true) {
        std::string topic = "topic_" + std::to_string(topic_number);
        std::string message = "Message on " + topic;

        zmq::message_t topic_msg(topic.data(), topic.size());
        zmq::message_t message_msg(message.data(), message.size());

        publisher.send(topic_msg, zmq::send_flags::sndmore);
        publisher.send(message_msg, zmq::send_flags::none);

        std::cout << "Published: " << message << std::endl;

        // Publish a message every second
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        topic_number = (topic_number % 3) + 1; // Change topic periodically
    }

    return 0;
}

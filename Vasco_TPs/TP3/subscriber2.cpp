// subscriber2.cpp
#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    zmq::context_t context(1);

    // Create a subscriber socket
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556"); // Connect to proxy XPUB

    // Subscribe to topic_2
    subscriber.set(zmq::sockopt::subscribe, "topic_2");

    std::cout << "Subscriber 2 started, listening to topic_2\n";

    while (true) {
        zmq::message_t topic;
        zmq::message_t message;

        // Receive topic
        subscriber.recv(topic, zmq::recv_flags::none);
        // Receive message
        subscriber.recv(message, zmq::recv_flags::none);

        std::string topic_str(static_cast<char*>(topic.data()), topic.size());
        std::string message_str(static_cast<char*>(message.data()), message.size());

        std::cout << "Subscriber 2 received [" << topic_str << "]: " << message_str << std::endl;
    }

    return 0;
}

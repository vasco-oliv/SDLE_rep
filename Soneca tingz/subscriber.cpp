#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);

    // Create a SUB socket
    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    
    subscriber.connect("tcp://localhost:6666");  // Change to new port


    // Subscribe to all messages (empty string subscribes to everything)
    subscriber.set(zmq::sockopt::subscribe, "");

    while (true) {
        zmq::message_t message;
        subscriber.recv(message, zmq::recv_flags::none);

        std::string received_message(static_cast<char*>(message.data()), message.size());
        std::cout << "Received: " << received_message << std::endl;
    }

    return 0;
}

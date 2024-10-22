// proxy.cpp
#include <zmq.hpp>
#include <iostream>

int main() {
    // Initialize ZeroMQ context
    zmq::context_t context(1);

    // Create XSUB socket to receive from publishers
    zmq::socket_t xsub_socket(context, ZMQ_XSUB);
    xsub_socket.bind("tcp://*:5555"); // bind to a specific port

    // Create XPUB socket to send to subscribers
    zmq::socket_t xpub_socket(context, ZMQ_XPUB);
    xpub_socket.bind("tcp://*:5556"); // bind to another port

    std::cout << "Proxy started: XSUB on tcp://*:5555, XPUB on tcp://*:5556\n";

    // Start proxy
    zmq::proxy(xsub_socket, xpub_socket, nullptr);

    return 0;
}

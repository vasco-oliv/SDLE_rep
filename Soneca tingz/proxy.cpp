#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);

    // Socket facing publishers
    zmq::socket_t xpub(context, zmq::socket_type::xpub);
    xpub.bind("tcp://*:6666");

    // Socket facing subscribers
    zmq::socket_t xsub(context, zmq::socket_type::xsub);
    xsub.bind("tcp://*:6667");

    std::cout << "Proxy running... \n";

    // Start the proxy to forward messages between publishers and subscribers
    zmq::proxy(xsub, xpub);

    return 0;
}

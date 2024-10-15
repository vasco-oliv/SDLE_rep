#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main (int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <server_id>" << std::endl;
        return 1;
    }
    
    std::string server_id = argv[1];
    
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, zmq::socket_type::rep);
    
    // Connect to the proxy instead of binding directly to a port
    socket.connect("tcp://localhost:5556");
    
    while (true) {
        zmq::message_t request;

        //  Wait for next request from client (via proxy)
        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Server " << server_id << " received: " << request.to_string() << std::endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to proxy
        zmq::message_t reply(5);
        memcpy(reply.data(), "World", 5);
        socket.send(reply, zmq::send_flags::none);
    }

    return 0;
}

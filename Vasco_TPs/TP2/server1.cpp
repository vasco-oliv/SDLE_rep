//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUSH);
    publisher.bind("tcp://*:5557");

    int taskNumber = 0;
    while (true) {
        std::string message = "Task " + std::to_string(taskNumber++);
        zmq::message_t msg(message.size());
        memcpy(msg.data(), message.c_str(), message.size());
        publisher.send(msg, zmq::send_flags::none);
        std::cout << "Sent: " << message << std::endl;

        sleep(1);
    }
    return 0;
}
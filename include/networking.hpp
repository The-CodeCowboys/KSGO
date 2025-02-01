#pragma once

#include <string>
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using std::string;

class Networking {

public:
    Networking(int rcvPort, string rcvIp, int sendPort, string sendIp);

private:
    io_context ioContext;
    ip::tcp::endpoint serverEndpoint;
    ip::tcp::socket serverSocket;

    void launchServer(int rcvPort, string rcvIp);
    void launchClient(int sendPort, string sendIp);

};

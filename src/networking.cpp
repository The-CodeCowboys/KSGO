#include "networking.hpp"

Networking::Networking(int rcvPort, string rcvIp, int sendPort, string sendIp) {
    this->launchServer(rcvPort, rcvIp);
    this->launchClient(rcvPort, rcvIp);
}

void Networking::launchServer(int rcvPort, string rcvIp) {
    std::cout << "launchServer start" << std::endl;

    this->serverEndpoint = ip::tcp::endpoint(ip::address::from_string(rcvIp), rcvPort);
    ip::tcp::socket serverSocket(this->ioContext, this->serverEndpoint);

    this->ioContext.run();

    std::cout << "launchServer end" << std::endl;
}

void Networking::launchClient(int sendPort, string sendIp) {
    std::cout << "launchClient start" << std::endl;

    this->ioContext.run();

    std::cout << "launchClient end" << std::endl;
}
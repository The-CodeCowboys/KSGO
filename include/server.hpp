#pragma once

#include "network.hpp"

class Server {
public:
    Server(std::string ip, int port);
    bool connectToClient();
    DataArray receiveData();
    void sendData(DataArray data);
    ~Server();

private:
    int tcpSocket;
    int clientSocket;
};

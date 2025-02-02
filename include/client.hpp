#pragma once

#include "network.hpp"

class Client {
public:
    Client();
    bool connectToServer(std::string ip, int port);
    DataArray receiveData();
    void sendData(DataArray data);
    ~Client();

private:
    int tcpSocket;
};

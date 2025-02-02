#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

using std::string;

class Client {
public:
    Client();
    bool connectToServer(string ip, int port);
    string readMsg();
    void sendMsg(string msg);
    ~Client();

private:
    int tcpSocket;
};

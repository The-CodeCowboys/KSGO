#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

using std::string;

class Server {
public:
    Server(int port);
    bool connectToClient();
    string readMsg();
    void sendMsg(string msg);
    ~Server();

private:
    int tcpSocket;
    int clientSocket;
};

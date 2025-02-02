#pragma once

#include "client.hpp"
#include "server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

using std::string;

class Network {
public:
    Network();

private:
    Client client;
    Server server;
};

#pragma once

#include "rtc/rtc.hpp"
#include <string>
#include <iostream>

using std::string;

class Networking {

public:
    Networking(string rcvIp, int rcvPort, string sendIp, int sendPort);
    rtc::Configuration config;
};

#include "network.hpp"
#include <thread>
#include <chrono>

const string ip = "locahost";
constexpr int port = 5023;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "One argument must be included" << std::endl;
        return 1;
    }

    string argument = argv[1];
    NetworkType networkType;

    if (argument.compare("server") == 0) {
        networkType = NetworkType::SERVER;
    } else if (argument.compare("client") == 0) {
        networkType = NetworkType::CLIENT;
    } else {
        std::cout << "Invalid argument" << std::endl;
        return 1;
    }

    Network::connect(networkType, ip, port);

    while (true) {
        if (networkType == NetworkType::CLIENT) {

            string msg = Network::read();
            if (msg.length() <= 0) {
                std::cout << "NO msg recieved" << std::endl;
            } else {
                std::cout << "YES msg recieved: " << msg << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

        } else {

            Network::send("Hello bro");
            std::cout << "Sending msg" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            
        }
    }

    return 0;
}

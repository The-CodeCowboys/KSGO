#include "server.hpp"
#include "client.hpp"

#include <thread>
#include <chrono>

constexpr int port = 5022;

void runServer() {
    std::cout << "2 RUNNING SERVER" << std::endl;

    Server server = Server(port);

    while (true) {
        bool isConnected = server.connectToClient();

        if (isConnected) {
            std::cout << "YES connected to client" << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "NOT connected to client" << std::endl;
    }

    while (true) {
        string msg = server.readMsg();
        if (msg.length() <= 0) {
            std::cout << "NO msg from client" << std::endl;
        } else {
            std::cout << "YES msg from client: " << msg << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // server.sendMsg("Hello from server");
        // std::cout << "Sending msg to server" << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    std::cout << "CLOSING SERVER" << std::endl;
}

void runClient() {
    std::cout << "2 RUNNING CLIENT" << std::endl;

    Client client = Client();

    while (true) {
        bool isConnected = client.connectToServer("localhost", port);

        if (isConnected) {
            std::cout << "YES connected to server" << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "NOT connected to server" << std::endl;
    }

    while (true) {
        // string msg = client.readMsg();
        // if (msg.length() <= 0) {
        //     std::cout << "NO msg from server" << std::endl;
        // } else {
        //     std::cout << "YES msg from server: " << msg << std::endl;
        // }
        // std::this_thread::sleep_for(std::chrono::seconds(1));

        client.sendMsg("Hello from client");
        std::cout << "Sending msg to server" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    std::cout << "CLOSING CLIENT" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "One argument must be included" << std::endl;
        return 1;
    }

    string argument = argv[1];

    if (argument.compare("server") == 0) {
        runServer();
    } else if (argument.compare("client") == 0) {
        runClient();
    } else {
        std::cout << "Invalid argument" << std::endl;
        return 1;
    }

    return 0;
}

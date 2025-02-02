#include "network.hpp"

NetworkType Network::networkType;
unique_ptr<Client> Network::client;
unique_ptr<Server> Network::server;

void Network::connect(NetworkType type, string ip, int port) {
    networkType = type;

    if (networkType == NetworkType::SERVER) {

        server = make_unique<Server>(port);
        while (true) {
            bool isConnected = server->connectToClient();
            if (isConnected) { return; }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }

    client = make_unique<Client>();
    while (true) {
        bool isConnected = client->connectToServer(ip, port);
        if (isConnected) { return; }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

NetworkType Network::type() {
    return networkType;
}

Data Network::getData() {
    return Data {
        type: DataType::NONE,
        posX: 0.0,
        posY: 0.0,
        directionX: 0.0,
        directionY: 0.0,
        isDead: false,
        hp: 0,
        level: 0,
        playerClass: ClassType::SNIPER
    };
}

void Network::sendData(Data data) {

}

string Network::read() {
    if (networkType == NetworkType::SERVER) {
        return server->readMsg();
    }
    return client->readMsg();
}

void Network::send(string msg) {
    if (networkType == NetworkType::SERVER) {
        return server->sendMsg(msg);
    }
    return client->sendMsg(msg);
}

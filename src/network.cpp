#include "network.hpp"

NetworkType Network::networkType;
unique_ptr<Client> Network::client;
unique_ptr<Server> Network::server;

void Network::connect(NetworkType type, string ip, int port) {
    networkType = type;

    if (networkType == NetworkType::SERVER) {
        server = make_unique<Server>(ip, port);
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

Data Network::receive() {
    DataArray dataArray;
    if (networkType == NetworkType::SERVER) {
        dataArray = server->receiveData();
    } else {
        dataArray = client->receiveData();
    }
    return dataArrayToData(dataArray);
}

void Network::send(Data data) {
    DataArray dataArray = dataToDataArray(data);
    if (networkType == NetworkType::SERVER) {
        return server->sendData(dataArray);
    } else {
        return client->sendData(dataArray);
    }
}

DataArray Network::dataToDataArray(Data data) {
    DataArray dataArray;
    std::memcpy(dataArray.data(), &data, DATA_SIZE);
    return dataArray;
}

Data Network::dataArrayToData(DataArray dataArray) {
    Data data;
    std::memcpy(&data, dataArray.data(), DATA_SIZE);
    return data;
}

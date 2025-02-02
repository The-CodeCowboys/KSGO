#include "server.hpp"

Server::Server(int port) {
    this->tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->tcpSocket < 0) {
        return;
    }
    int flags = fcntl(this->tcpSocket, F_GETFL, 0);
    fcntl(this->tcpSocket, F_SETFL, flags | O_NONBLOCK);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(this->tcpSocket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        return;
    }
    if (listen(this->tcpSocket, 5) < 0) {
        return;
    }
}

bool Server::connectToClient() {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    this->clientSocket = accept(this->tcpSocket, (sockaddr*)&client_addr, &client_len);
    if (this->clientSocket < 0) {
        return false;
    }
    int flags = fcntl(this->clientSocket, F_GETFL, 0);
    fcntl(this->clientSocket, F_SETFL, flags | O_NONBLOCK);
    return true;
}

DataArray Server::receiveData() {
    char buffer[1024];
    ssize_t msg_size = recv(this->clientSocket, buffer, sizeof(buffer), 0);
    if (msg_size <= 0) {
        return Network::dataToDataArray(DEFAULT_DATA);
    }
    DataArray data;
    std::memcpy(data.data(), buffer, DATA_SIZE);

    return data;
}

void Server::sendData(DataArray data) {
    send(this->clientSocket, data.data(), data.size(), 0);
}

Server::~Server() {
    close(this->tcpSocket);
    close(this->clientSocket);
}

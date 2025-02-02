#include "client.hpp"

Client::Client() {
    this->tcpSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->tcpSocket < 0) {
        return;
    }
}

bool Client::connectToServer(string ip, int port) {
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
    if (connect(this->tcpSocket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        return false;
    }
    int flags = fcntl(this->tcpSocket, F_GETFL, 0);
    fcntl(this->tcpSocket, F_SETFL, flags | O_NONBLOCK);
    return true;
}

DataArray Client::receiveData() {
    DataArray data;
    ssize_t msg_size = recv(this->tcpSocket, data.data(), data.size(), 0);
    if (msg_size <= 0) {
        return Network::dataToDataArray(DEFAULT_DATA);
    }
    return data;
}

void Client::sendData(DataArray data) {
    send(this->tcpSocket, data.data(), data.size(), 0);
}

Client::~Client() {
    close(this->tcpSocket);
}

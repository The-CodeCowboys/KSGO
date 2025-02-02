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

string Client::readMsg() {
    char buffer[1024];
    ssize_t msg_size = recv(this->tcpSocket, buffer, sizeof(buffer), 0);
    if (msg_size <= 0) {
        return "";
    }
    return string(buffer, msg_size);
}

void Client::sendMsg(string msg) {
    ssize_t bytes_sent = send(this->tcpSocket, msg.c_str(), msg.size(), 0);
}

Client::~Client() {
    close(this->tcpSocket);
}

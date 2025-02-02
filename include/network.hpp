#pragma once

#include "client.hpp"
#include "server.hpp"
#include <thread>
#include <chrono>
#include <memory>

using std::string;
using std::unique_ptr;
using std::make_unique;

enum class NetworkType { SERVER, CLIENT };
enum class DataType { NONE, BULLET, PLAYER, HIT, DEATH, ROUND_END, ROUND_START };
enum class ClassType { SNIPER, RIFLE, SHOTGUN };

struct Data {
    DataType type;
    float posX;
    float posY;
    float directionX;
    float directionY;
    bool isDead; // isDead / didHostWin
    int hp;      // hp / currentHostPoints
    int level;   // level / currentPlayerPoints
    ClassType playerClass;
};

class Network {
public:
    // Function is blocking
    // NetworkType::SERVER ip parameter is unused
    // NetworkType::CLIENT ip parameter is used
    static void connect(NetworkType type, string ip, int port);

    // Return a Data object
    // Non-blocking function
    // If (data.type == DataType::NONE) it means no data has been recieved
    static Data getData();

    // Send a Data object
    static void sendData(Data data);

    // Return the NetworkType (Host or Client)
    static NetworkType type();

    static string read(); // TEMP TODO
    static void send(string msg); // TEMP TODO

private:
    static NetworkType networkType;
    static unique_ptr<Client> client;
    static unique_ptr<Server> server;

    // static string read();
    // static void send(string msg);
};

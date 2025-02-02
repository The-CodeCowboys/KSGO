#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <array>
#include <thread>
#include <chrono>
#include <string>
#include <memory>
#include <cstring>

// constexpr int DATA_SIZE = sizeof(Data);
constexpr int DATA_SIZE = 36UL;
typedef std::array<char, DATA_SIZE> DataArray;

#include "client.hpp"
#include "server.hpp"

using std::string;
using std::unique_ptr;
using std::make_unique;

enum class NetworkType { SERVER=0, CLIENT=1 };
enum class DataType { NONE=0, BULLET=1, PLAYER=2, HIT=3, DEATH=4, ROUND_END=5, ROUND_START=6 };
enum class ClassType { SNIPER=0, RIFLE=1, SHOTGUN=2 };

class Client;
class Server;

struct Data {
    DataType type;
    float posX;
    float posY;
    float directionX;
    float directionY;
    bool isDead; // isDead / didHostWin
    int hp;      // hp / currentHostPoints
    int level;   // level / currentPlayerPoints
    ClassType classType;
};

const Data DEFAULT_DATA = {
    type: DataType::NONE,
    posX: 0.0,
    posY: 0.0,
    directionX: 0.0,
    directionY: 0.0,
    isDead: false,
    hp: 0,
    level: 0,
    classType: ClassType::SNIPER
};

class Network {
public:
    // Function is blocking
    // NetworkType::SERVER ip parameter is unused
    // NetworkType::CLIENT ip parameter is used
    static void connect(NetworkType type, string ip, int port);

    // Send a Data object
    static void send(Data data);

    // Return a Data object
    // Non-blocking function
    // If (data.type == DataType::NONE) it means no data has been recieved
    static Data receive();

    // Return the NetworkType (Host or Client)
    static NetworkType type();

    static DataArray dataToDataArray(Data data);
    static Data dataArrayToData(DataArray dataArray);

private:
    static NetworkType networkType;
    static unique_ptr<Client> client;
    static unique_ptr<Server> server;
};

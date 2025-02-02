#include "network.hpp"

const string ip = "locahost";
constexpr int port = 5027;

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
        if (networkType == NetworkType::SERVER) {

            Data data = Network::receive();
            if (data.type == DataType::NONE) {
                std::cout << "NO" << std::endl;
            } else {
                switch (data.classType) {
                    case ClassType::SHOTGUN: std::cout << "YES shotgun" << std::endl; break;
                    case ClassType::SNIPER:  std::cout << "YES sniper"  << std::endl; break;
                    case ClassType::RIFLE:   std::cout << "YES rifle"   << std::endl; break;
                    default:                 std::cout << "YES error"   << std::endl; break;
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

        } else {

            Network::send({
                type: DataType::PLAYER,
                posX: 0.0,
                posY: 0.0,
                directionX: 0.0,
                directionY: 0.0,
                isDead: false,
                hp: 0,
                level: 0,
                classType: ClassType::SNIPER
            });
            std::cout << "Sending msg" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));


            Network::send({
                type: DataType::PLAYER,
                posX: 0.0,
                posY: 0.0,
                directionX: 0.0,
                directionY: 0.0,
                isDead: false,
                hp: 0,
                level: 0,
                classType: ClassType::SHOTGUN
            });
            std::cout << "Sending msg" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));


            Network::send({
                type: DataType::PLAYER,
                posX: 0.0,
                posY: 0.0,
                directionX: 0.0,
                directionY: 0.0,
                isDead: false,
                hp: 0,
                level: 0,
                classType: ClassType::SHOTGUN
            });
            std::cout << "Sending msg" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));


            Network::send({
                type: DataType::PLAYER,
                posX: 0.0,
                posY: 0.0,
                directionX: 0.0,
                directionY: 0.0,
                isDead: false,
                hp: 0,
                level: 0,
                classType: ClassType::RIFLE
            });
            std::cout << "Sending msg" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    return 0;
}

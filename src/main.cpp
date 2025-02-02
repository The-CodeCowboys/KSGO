#include "components.hpp"
#include "constants.hpp"
#include "map.hpp"
#include "network.hpp"
#include "scenes.hpp"
#include <cstdio>
#include <raylib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "One argument must be included" << std::endl;
        return 1;
    }

    std::string argument = argv[1];
    NetworkType networkType;

    if (argument.compare("server") == 0) {
        networkType = NetworkType::SERVER;
    } else if (argument.compare("client") == 0) {
        networkType = NetworkType::CLIENT;
    } else {
        std::cout << "Invalid argument" << std::endl;
        return 1;
    }

    Network::connect(networkType, "0.0.0.0", 5557);

    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ks:go");
    SetTargetFPS(60);

    Map gameMap;
    gameMap.initMap();

    SceneManager sceneManager{};
    sceneManager.setScene(std::make_unique<TitleScene>(sceneManager));

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            sceneManager.getScene().draw();
            sceneManager.getScene().update();
        }
        EndDrawing();
    }

    return 0;
}

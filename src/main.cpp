#include <algorithm>
#include <array>
#include <cstdio>
#include <raylib.h>
#include <vector>
#include "constants.hpp"
#include "DynamicEntity.hpp"
#include "Player.hpp"
#include "StaticEntity.hpp"
#include "Weapon.hpp"
#include "map.hpp"
#include "network.hpp"

std::array<StaticEntity, 50> staticEntities = {};
std::vector<DynamicEntity*> dynamicEntities = {};
std::vector<DynamicEntity*> dynamicBullets = {};
Camera2D camera = {0};

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

    Network::connect(networkType, "localhost", 5500);

    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ks:go");
    SetTargetFPS(60);

    Map gameMap;
    gameMap.initMap();
    M4A4 loadout = {10, 10, 2, 0.2f};
    AWP loadout2 = {10, 10, 2, 3};
    NOVA loadout3 = {100, 10, 2, 2};
    float playerSpeed = 10;
    Player player = {{1200, 200}, 100, playerSpeed, loadout};
    camera.target = (Vector2) {player.getPosition()};
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    if (Network::type() == NetworkType::CLIENT) {
        player.position.y = 2700;
    }

    

// enum class DataType { NONE=0, BULLET=1, PLAYER=2, HIT=3, DEATH=4, ROUND_END=5, ROUND_START=6 };
    // Gameloop

    while (!WindowShouldClose()) {
        Data data = Network::receive();
        switch (data.type) {
        case DataType::NONE: 
            break;

        case DataType::BULLET: 
            break;

        case DataType::PLAYER: 
                dynamicEntities.back()->hitBox.x = data.posX; 
                dynamicEntities.back()->hitBox.y = data.posY; 
                printf("posx: %f\n", data.posX);
                printf("posy: %f\n", data.posY);
            break;
        
        case DataType::HIT: 
            break;
        
        case DataType::DEATH: 
            break;

        case DataType::ROUND_END: 
            break;

        case DataType::ROUND_START: 
            break;

        }

        // Draw
        BeginDrawing();            
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                DrawRectangle(-2000, -1000, 10000, 10000, BROWN);
                DrawRectangle(1000, 0, 1000, 500, GREEN);
                DrawRectangle(1000, 2500, 1000, 500, YELLOW);
                player.update();
            
                for (DynamicEntity* bullet : dynamicBullets) {
                    bullet->move();
                    bullet->render(BLUE);
                }

                for (DynamicEntity* entity : dynamicEntities) {
                    entity->render(RED);
                }

                for (StaticEntity staticEntity : staticEntities) {
                    staticEntity.render();
                }

                // Entity Collision Logic

                for (DynamicEntity* entity : dynamicEntities) {
                    for (DynamicEntity* bullet : dynamicBullets) {
                        if (CheckCollisionRecs(entity->getHitBox(), bullet->getHitBox())) {
                            entity->loseHealth(bullet->getDamage());

                            auto it = find(dynamicBullets.begin(), dynamicBullets.end(), bullet);
                            if (it != dynamicBullets.end() && bullet != nullptr) {
                                dynamicBullets.erase(it);
                                delete bullet;
                            }

                            // dynamicBullets.erase(std::remove(dynamicBullets.begin(), dynamicBullets.end(), bullet), dynamicBullets.end());
                            // delete bullet;


                            // Check for where player dies
                            if (entity->getHealth() <= 0) {
                                delete entity;
                                dynamicEntities.erase(std::remove(dynamicEntities.begin(), dynamicEntities.end(), entity), dynamicEntities.end());
                            }
                        }
                    }
                }

                for (StaticEntity staticEntity : staticEntities) {
                    for (DynamicEntity* bullet : dynamicBullets) {
                        if (CheckCollisionRecs(staticEntity.hitBox, bullet->getHitBox())) {
                            auto it = find(dynamicBullets.begin(), dynamicBullets.end(), bullet);
                            if (it != dynamicBullets.end() && bullet != nullptr) {
                                dynamicBullets.erase(it);
                                delete bullet;
                            }
                        }
                    }
                }

                // Static Entity Collision Logic

                    for (StaticEntity staticEntity : staticEntities) {
                        if (CheckCollisionRecs(player.getHitBox(), staticEntity.hitBox)) {
                            if (IsKeyDown(KEY_W)) {
                                player.setPosition({0, playerSpeed});
                            }

                            if (IsKeyDown(KEY_A)) {
                                player.setPosition({playerSpeed, 0});
                            }

                            if (IsKeyDown(KEY_S)) {
                                player.setPosition({0, -playerSpeed});
                            }

                            if (IsKeyDown(KEY_D)) {
                                player.setPosition({-playerSpeed, 0});
                            }
                        }
                    }

            EndMode2D();
        EndDrawing();

        // Update
        camera.target = (Vector2) {player.getPosition()}; // Might want to pass the camera as a parameter of the player

    }

    // Exit
    return 0;
}

#include <algorithm>
#include <array>
#include <raylib.h>
#include <vector>
#include "constants.hpp"
#include "DynamicEntity.hpp"
#include "Player.hpp"
#include "StaticEntity.hpp"
#include "Weapon.hpp"

std::array<StaticEntity, 50> staticEntities = {};
std::vector<DynamicEntity*> dynamicEntities = {};
std::vector<DynamicEntity*> dynamicBullets = {};
Camera2D camera = {0};

int main(void) {
    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ks:go");
    SetTargetFPS(60);

    M4A4 loadout;
    Player player = {{100, 100}, 100, 5, loadout};
    camera.target = (Vector2) {player.getPosition()};
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    // MAP
        Texture2D wallTex;
        Rectangle rect = {.x = 200, .y = 200, .width = 100, .height = 100};
        Image img = LoadImage("../gun.jpg");
        ImageResize(&img, 100, 100);
        ImageDrawPixelV(&img, {0, 0}, GRAY);
        wallTex = LoadTextureFromImage(img);
        StaticEntity wall = {.position = {200, 200}, .texture = wallTex, .hitBox = rect};
        staticEntities[0] = wall;


    // Gameloop

    while (!WindowShouldClose()) {

        // Draw

        BeginDrawing();            
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                DrawRectangle(500, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);
                player.update();
            
                for (DynamicEntity* bullet : dynamicBullets) {
                    bullet->move();
                    bullet->render();
                }

                for (DynamicEntity* bullet : dynamicEntities) {
                    bullet->render();
                }

                for (StaticEntity staticEntity : staticEntities) {
                    staticEntity.render();
                }

                // Entity Collision Logic

                for (DynamicEntity* entity : dynamicEntities) {
                    for (DynamicEntity* bullet : dynamicBullets) {
                        if (CheckCollisionRecs(entity->getHitBox(), bullet->getHitBox())) {
                            delete bullet;
                            dynamicBullets.erase(std::remove(dynamicBullets.begin(), dynamicBullets.end(), bullet), dynamicBullets.end());
                            // Remove health
                        }
                    }
                }

                for (StaticEntity staticEntity : staticEntities) {
                    for (DynamicEntity* bullet : dynamicBullets) {
                        if (CheckCollisionRecs(staticEntity.hitBox, bullet->getHitBox())) {
                            delete bullet;
                            dynamicBullets.erase(std::remove(dynamicBullets.begin(), dynamicBullets.end(), bullet), dynamicBullets.end());
                            // Remove health
                        }
                    }
                }

                for (DynamicEntity* entity : dynamicEntities) {
                    for (DynamicEntity* bullet : dynamicBullets) {
                        if (CheckCollisionRecs(entity->getHitBox(), bullet->getHitBox())) {
                            delete bullet;
                            dynamicBullets.erase(std::remove(dynamicBullets.begin(), dynamicBullets.end(), bullet), dynamicBullets.end());
                            // Remove health
                        }
                    }
                }

                // Static Entity Collision Logic

                    for (StaticEntity staticEntity : staticEntities) {
                        if (CheckCollisionRecs(player.getHitBox(), staticEntity.hitBox)) {
                            if (IsKeyDown(KEY_W)) {
                                player.setPosition({0, 5});
                            }

                            if (IsKeyDown(KEY_A)) {
                                player.setPosition({5, 0});
                            }

                            if (IsKeyDown(KEY_S)) {
                                player.setPosition({0, -5});
                            }

                            if (IsKeyDown(KEY_D)) {
                                player.setPosition({-5, 0});
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

#include "constants.hpp"
#include <memory>
#include <raylib.h>
#include <scenes.hpp>

int main(void) {
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    SetTargetFPS(60);

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

    CloseWindow();

    return 0;
}

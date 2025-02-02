#include <memory>
#include <raylib.h>
#include <scenes.hpp>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;

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

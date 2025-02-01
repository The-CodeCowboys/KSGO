#include <SceneManager.hpp>
#include <memory>
#include <raylib.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    SetTargetFPS(60);

    std::unique_ptr<Scene> currentScene = std::make_unique<TitleScene>();

    while (!WindowShouldClose()) {

        BeginDrawing();
        {
            currentScene->draw();
            currentScene->update();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

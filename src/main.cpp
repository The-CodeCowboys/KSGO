#include "raylib.h"
#include "Networking.hpp"

int main(void) {
    Networking::startConnection();

    // const int screenWidth = 800;
    // const int screenHeight = 450;
    // InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    // SetTargetFPS(60);
    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);
    //     DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    //     EndDrawing();
    // }
    // CloseWindow();

    while (true) {}

    return 0;
}

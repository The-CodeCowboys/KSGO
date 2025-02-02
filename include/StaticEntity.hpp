#pragma once

#include <raylib.h>
struct StaticEntity {
    Vector2 position;
    Texture2D texture;
    Rectangle hitBox;

    void render() {
        DrawTextureV(texture, position, RED);
    }
};

#pragma once
#include <raylib.h>

class StaticEntity {
public:
    Vector2 position;
    Texture2D texture;
    Rectangle hitBox;

    void render();
};

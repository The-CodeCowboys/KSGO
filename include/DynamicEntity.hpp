#pragma once
#include <raylib.h>

class DynamicEntity {

public: 
    DynamicEntity(Vector2 position, Vector2 size, Texture2D texture, Rectangle hitBox, int health);
    void move();
    void render();
    Rectangle getHitBox();
private:
    Vector2 direction;
    Vector2 size;
    Texture2D texture;
    Rectangle hitBox;
    int health;
};

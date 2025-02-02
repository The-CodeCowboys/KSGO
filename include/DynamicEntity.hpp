#pragma once
#include <raylib.h>

class DynamicEntity {

public: 
    Rectangle hitBox;
    DynamicEntity(Vector2 position, Vector2 size, Texture2D texture, Rectangle hitBox, int health, int damage);
    void move();
    void render(Color color);
    Rectangle getHitBox();
    int getDamage();
    int getHealth();
    void loseHealth(int newHealth);
private:
    Vector2 direction;
    Vector2 size;
    Texture2D texture;
    int health;
    int damage;
};

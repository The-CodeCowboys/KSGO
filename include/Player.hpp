#pragma once
#include "Weapon.hpp"
#include <raylib.h>

class Player {
    public:
    Player();
    Vector2 position;
    int health;
    Player(Vector2 position, int health, float speed, IWeapon& weapon);
    void update();
    Vector2 getPosition();
    Rectangle getHitBox();
    int getHealth();
    void setPosition(Vector2 position);
    void move();
    void shoot();
    void render();

    private:
    Texture2D playerTexture;
    Rectangle playerHitBox;
    bool orientation;
    float speed;
    IWeapon* weapon;

    private:
};

#pragma once
#include "Weapon.hpp"
#include <algorithm>
#include <memory>
#include <raylib.h>

class Player {
    public:
        Vector2 position;
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
        int health;
        float speed;
        IWeapon* weapon;
        
    private:

};

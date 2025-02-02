#include "DynamicEntity.hpp"
#include <raylib.h>

DynamicEntity::DynamicEntity(Vector2 position, Vector2 size, Texture2D texture, Rectangle hitBox, int health, int damage) {
    this->direction = position;
    this->size = size;
    this->texture = texture;
    this->hitBox = hitBox;
    this->health = health;
    this->damage = damage;
}

int DynamicEntity::getHealth() {
    return this->health;
}

int DynamicEntity::getDamage() {
    return this->damage;
}

void DynamicEntity::loseHealth(int damage) {
    this->health -= damage;
}

void DynamicEntity::move() {
    this->hitBox.x += direction.x / 5;
    this->hitBox.y += direction.y / 5;
}

void DynamicEntity::render(Color color) {

    DrawRectangleRec(this->hitBox, color);
}

Rectangle DynamicEntity::getHitBox() {
    return hitBox;
}

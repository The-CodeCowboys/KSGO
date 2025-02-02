#include "DynamicEntity.hpp"
#include <raylib.h>

DynamicEntity::DynamicEntity(Vector2 position, Vector2 size, Texture2D texture, Rectangle hitBox, int health) {
    this->direction = position;
    this->size = size;
    this->texture = texture;
    this->hitBox = hitBox;
    this->health = health;
}

void DynamicEntity::move() {
    this->hitBox.x += direction.x / 5;
    this->hitBox.y += direction.y / 5;
}

void DynamicEntity::render() {

    DrawRectangleRec(this->hitBox, YELLOW);
}

Rectangle DynamicEntity::getHitBox() {
    return hitBox;
}

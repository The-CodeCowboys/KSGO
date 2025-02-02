#include "Player.hpp"
#include <raylib.h>


Player::Player(Vector2 position, int health, float speed, IWeapon& weapon) {
    this->position = position;
    this->health = health;
    this->speed = speed;
    this->weapon = &weapon;
    this->weapon->linkToPlayer(this->position);
    this->playerHitBox = {this->position.x, this->position.y, 50, 50};
}

void Player::update() {
    move();
    this->weapon->linkToPlayer(this->position);
    this->weapon->shoot();
    render();
}

Vector2 Player::getPosition() {
    return this->position;
}

void Player::setPosition(Vector2(position)) {
    this->position.x += position.x;
    this->position.y += position.y;
    this->playerHitBox.x = this->position.x;
    this->playerHitBox.y = this->position.y;
}

int Player::getHealth() {
    return this->health;;
}

Rectangle Player::getHitBox() {
    return this->playerHitBox;
}

void Player::render() {
    DrawRectangle(position.x, position.y, 50, 50, RED);
    this->weapon->render();
    
}

void Player::move() {
    if (IsKeyDown(KEY_W)) {
        this->position.y -= speed;
        this->playerHitBox.y = this->position.y;
    }

    if (IsKeyDown(KEY_A)) {
        this->position.x -= speed;
        this->playerHitBox.x = this->position.x;
    }

    if (IsKeyDown(KEY_S)) {
        this->position.y += speed;
        this->playerHitBox.y = this->position.y;
    }

    if (IsKeyDown(KEY_D)) {
        this->position.x += speed;
        this->playerHitBox.x = this->position.x;
    }
}

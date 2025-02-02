#include "Weapon.hpp"
#include "constants.hpp"
#include "DynamicEntity.hpp"
#include "network.hpp"
#include <cmath>
#include <complex>
#include <cstdio>
#include <raylib.h>
#include <rlgl.h>
#include <vector>

extern std::vector<DynamicEntity*> dynamicBullets;
extern Camera2D camera;


M4A4::M4A4(int ammo, int damage, int recoil, float firingSpeed) {
    this->ammo = ammo;
    this->damage = damage;
    this->recoil = recoil;
    this->firingSpeed = firingSpeed;
    this->canShoot = true;
    this->shootTime = 0;
}

void M4A4::linkToPlayer(Vector2& position) {
    this->position = position;
}


void M4A4::render() {
    // Rectangle rec = {this->position.x, this->position.y, 10, 20};
    // float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
    // float y = -GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y + this->position.y;
    // float angle = -atan2(y, x) * (180/PI);
    // 
    // Image img = LoadImage("../gun.jpg");
    // ImageResize(&img, 60, 60);
    // ImageRotate(&img, angle);
    // ImageDrawPixelV(&img, this->position, GRAY);
    // this->texture = LoadTextureFromImage(img);
    // DrawTexture(this->texture, this->position.x + 10, this->position.y + 10, WHITE);
    // UnloadImage(img);
}

void M4A4::shoot() {
    float deltaTime = GetTime() - this->shootTime;

    if (canShoot && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->ammo > 0 && deltaTime > this->firingSpeed) {
        this->shootTime = GetTime();
        ammo--;
        Texture2D test;
        Image img = LoadImage("../gun.jpg");
        ImageDrawPixelV(&img, this->position, GRAY);
        test = LoadTextureFromImage(img);
        float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
        float y = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y - this->position.y;

        float norm = sqrt(x*x + y*y);
        x = (x / norm) * 20;
        y = (y / norm) * 20;

        DynamicEntity* bullet = new DynamicEntity({x, y}, {40, 40}, test, {this->position.x + x*8, this->position.y + y*8, 40, 40}, 1, this->damage);
        Network::send({DataType::BULLET, this->position.x, this->position.y, x, y, false, 0, 0});
        dynamicBullets.push_back(bullet);
    }
}

/************************************************/

AWP::AWP(int ammo, int damage, int recoil, float firingSpeed) {
    this->ammo = ammo;
    this->damage = damage;
    this->recoil = recoil;
    this->firingSpeed = firingSpeed;
    this->canShoot = true;
    this->shootTime = 0;
}

void AWP::linkToPlayer(Vector2& position) {
    this->position = position;
}


void AWP::render() {
    Rectangle rec = {this->position.x, this->position.y, 10, 20};
    float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
    float y = -GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y + this->position.y;
    float angle = -atan2(y, x) * (180/PI);
    
    Image img = LoadImage("../sniper.jpg");
    ImageResize(&img, 60, 60);
    ImageRotate(&img, angle);
    ImageDrawPixelV(&img, this->position, GRAY);
    this->texture = LoadTextureFromImage(img);
    DrawTexture(this->texture, this->position.x + 10, this->position.y + 10, WHITE);
    UnloadImage(img);
}

void AWP::shoot() {
    float deltaTime = GetTime() - this->shootTime;

    if (canShoot && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->ammo > 0 && deltaTime > this->firingSpeed) {
        this->shootTime = GetTime();
        ammo--;
        Texture2D test;
        Image img = LoadImage("../gun.jpg");
        ImageDrawPixelV(&img, this->position, GRAY);
        test = LoadTextureFromImage(img);
        float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
        float y = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y - this->position.y;

        float norm = sqrt(x*x + y*y);
        x = (x / norm) * 100;
        y = (y / norm) * 100;

        DynamicEntity* bullet = new DynamicEntity({x, y}, {40, 40}, test, {this->position.x + x*8, this->position.y + y*8, 20, 30}, 1, this->damage);
        Network::send({DataType::BULLET, this->position.x, this->position.y, x, y, false, 0, 0});
        dynamicBullets.push_back(bullet);
    }
}


/************************************************/

NOVA::NOVA(int ammo, int damage, int recoil, float firingSpeed) {
    this->ammo = ammo;
    this->damage = damage;
    this->recoil = recoil;
    this->firingSpeed = firingSpeed;
    this->canShoot = true;
    this->shootTime = 0;
}

void NOVA::linkToPlayer(Vector2& position) {
    this->position = position;
}


void NOVA::render() {
    Rectangle rec = {this->position.x, this->position.y, 10, 20};
    float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
    float y = -GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y + this->position.y;
    float angle = -atan2(y, x) * (180/PI);
    
    Image img = LoadImage("../shogun.jpg");
    // printf("Angle: %f \n", angle);
    // printf("mouse X: %f \n", x);
    // printf("mouse Y: %f \n", y);
    // printf("obj X: %f \n", this->position.x);
    // printf("obj Y: %f \n", this->position.y);
    ImageResize(&img, 60, 60);
    ImageRotate(&img, angle);
    ImageDrawPixelV(&img, this->position, GRAY);
    this->texture = LoadTextureFromImage(img);
    DrawTexture(this->texture, this->position.x + 10, this->position.y + 10, WHITE);
    UnloadImage(img);
}

void NOVA::shoot() {

    float deltaTime = GetTime() - this->shootTime;

    if (canShoot && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->ammo > 0 && deltaTime > firingSpeed) {
        this->shootTime = GetTime();
        ammo -= 4;
        Texture2D test;
        Image img = LoadImage("../gun.jpg");
        ImageDrawPixelV(&img, this->position, GRAY);
        test = LoadTextureFromImage(img);
        float x = (GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x);
        float y = (GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y - this->position.y);

        float norm = sqrt(x*x + y*y);
        x = (x / norm) * 100;
        y = (y / norm) * 100;

        printf("x: %f\n", x);
        printf("y: %f\n", y);

        DynamicEntity* bullet0 = new DynamicEntity({x+ 10, y+10}, {40, 40}, test, {this->position.x + x*8, this->position.y + y*8, 20, 30}, 1, this->damage);
        DynamicEntity* bullet1 = new DynamicEntity({x-10, y-10}, {40, 40}, test, {this->position.x + x*8, this->position.y + y*8, 20, 30}, 1, this->damage);
        DynamicEntity* bullet2 = new DynamicEntity({x-20, y-20}, {40, 40}, test, {this->position.x + x*8, this->position.y + y*8, 20, 30}, 1, this->damage);
        DynamicEntity* bullet3 = new DynamicEntity({x, y}, {40, 40}, test, {this->position.x, this->position.y, 20, 30}, 1, this->damage);

        Network::send({DataType::BULLET, this->position.x, this->position.y, x, y, false, 0, 0});
        dynamicBullets.push_back(bullet0);
        dynamicBullets.push_back(bullet1);
        dynamicBullets.push_back(bullet2);
        dynamicBullets.push_back(bullet3);
    }
}

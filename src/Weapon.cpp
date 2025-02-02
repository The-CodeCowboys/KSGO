#include "Weapon.hpp"
#include "DynamicEntity.hpp"
#include <cmath>
#include <cstdio>
#include <raylib.h>
#include <rlgl.h>
#include <vector>

extern std::vector<DynamicEntity*> dynamicBullets;
extern std::vector<DynamicEntity*> dynamicEntities;
extern Camera2D camera;


M4A4::M4A4() {
}

void M4A4::linkToPlayer(Vector2& position) {
    this->position = position;
}


void M4A4::render() {
    Rectangle rec = {this->position.x, this->position.y, 10, 20};
    float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
    float y = -GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y + this->position.y;
    float angle = -atan2(y, x) * (180/PI);
    
    // Image img = LoadImage("../gun.jpg");
    // // printf("Angle: %f \n", angle);
    // // printf("mouse X: %f \n", x);
    // // printf("mouse Y: %f \n", y);
    // // printf("obj X: %f \n", this->position.x);
    // // printf("obj Y: %f \n", this->position.y);
    // ImageResize(&img, 60, 60);
    // ImageRotate(&img, angle);
    // ImageDrawPixelV(&img, this->position, GRAY);
    // this->texture = LoadTextureFromImage(img);
    // DrawTexture(this->texture, this->position.x + 10, this->position.y + 10, WHITE);
    // UnloadImage(img);
    // UnloadTexture(this->texture);
}

void M4A4::shoot() {
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Texture2D test;
        Image img = LoadImage("../gun.jpg");
        ImageDrawPixelV(&img, this->position, GRAY);
        test = LoadTextureFromImage(img);
        float x = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).x - this->position.x;
        float y = GetScreenToWorld2D({(float)GetMouseX(), (float)GetMouseY()}, camera).y + this->position.y;

        printf("mouse X: %f \n", x);
        printf("mouse Y: %f \n", y);
        DynamicEntity* bullet = new DynamicEntity({x + 100, y}, {40, 40}, test, {this->position.x, this->position.y, 50, 30}, 1);
        DynamicEntity* entity = new DynamicEntity({x, y}, {40, 40}, test, {50, 50, 100, 100}, 100);
        dynamicBullets.push_back(bullet);
        dynamicEntities.push_back(entity);
    }
}

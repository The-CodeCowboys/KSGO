#include "StaticEntity.hpp"
#include <raylib.h>
#include <array>
#include "DynamicEntity.hpp"
#include <vector>
#include "map.hpp"

extern std::array<StaticEntity, 50> staticEntities;
extern std::vector<DynamicEntity*> dynamicEntities;

StaticEntity createStaticEntity(Vector2 position, Vector2 size, Image image, bool collision) {
        StaticEntity staticEntity;
        staticEntity.position = position;
        Rectangle rect;
        if (collision) {
            rect = {position.x, position.y, size.x, size.y};
        }
        else {
            rect = {-1000, -1000, 0, 0};
        }
        ImageResize(&image, size.x, size.y); 
        ImageDrawPixelV(&image, {0, 0}, WHITE);
        staticEntity.texture = LoadTextureFromImage(image);
        staticEntity.hitBox = rect;
        UnloadImage(image);

        return staticEntity;
}


StaticEntity createTree(Vector2 position, Vector2 size, Image image) {
        StaticEntity staticEntity;
        staticEntity.position = position;
        Rectangle rect = {position.x, position.y + size.y / 1.2f, size.x, size.y / 7};
        ImageResize(&image, size.x, size.y); 
        ImageDrawPixelV(&image, {0, 0}, WHITE);
        staticEntity.texture = LoadTextureFromImage(image);
        staticEntity.hitBox = rect;
        UnloadImage(image);

        return staticEntity;
}

void Map::initMap() {
        Vector2 mapSize = {100, 3000};
        StaticEntity rightWall = createStaticEntity({0, 0}, mapSize, LoadImage("../wall.jpg"), true);
        StaticEntity topWall = createStaticEntity({0, 0}, {mapSize.y, mapSize.x}, LoadImage("../wall.jpg"), true);
        StaticEntity leftWall = createStaticEntity({mapSize.y, 0}, mapSize, LoadImage("../wall.jpg"), true);
        StaticEntity bottomWall = createStaticEntity({0, mapSize.y}, {mapSize.y + 100, mapSize.x}, LoadImage("../wall.jpg"), true);

        StaticEntity bush = createStaticEntity({1500, 1500}, {150, 150}, LoadImage("../bullet.jpg"), false);

        StaticEntity stone = createStaticEntity({2500, 2500}, {200, 200}, LoadImage("../stone.jpg"), true);

        StaticEntity coverHost = createStaticEntity({1350, 600}, {300, 100}, LoadImage("../stone.jpg"), true);
        StaticEntity coverClient = createStaticEntity({1350, 2300}, {300, 100}, LoadImage("../stone.jpg"), true);

        StaticEntity tree0 = createTree({700, 1200}, {200, 400}, LoadImage("../stone.jpg"));
        StaticEntity tree1 = createTree({2300, 1700}, {200, 400}, LoadImage("../stone.jpg"));

        staticEntities[0] = rightWall;
        staticEntities[1] = topWall;
        staticEntities[2] = leftWall;
        staticEntities[3] = bottomWall;
        // staticEntities[4] = bush;
        staticEntities[5] = stone;
        staticEntities[6] = coverHost;
        staticEntities[7] = coverClient;
        staticEntities[8] = tree0;
        staticEntities[9] = tree1;

        Image enemie = LoadImage("../bullet.jpg");
        ImageDrawPixelV(&enemie, {0, 0}, WHITE);
        DynamicEntity* entity = new DynamicEntity({1500, 2700}, {40, 40}, LoadTextureFromImage(enemie), {1500, 2700, 100, 100}, 1000, 0);
        UnloadImage(enemie);
        dynamicEntities.push_back(entity);
}

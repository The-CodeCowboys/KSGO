#include "StaticEntity.hpp"
#include <raylib.h>
#include <array>
#include "DynamicEntity.hpp"
#include <vector>
#include "map.hpp"

extern std::array<StaticEntity, 50> staticEntities;
extern std::vector<DynamicEntity*> dynamicEntities;

StaticEntity createStaticEntity(Vector2 position, Vector2 size, Image image) {
        StaticEntity staticEntity;
        staticEntity.position = position;
        Rectangle rightRect = {position.x, position.y, size.x, size.y};
        ImageResize(&image, size.x, size.y); 
        ImageDrawPixelV(&image, {0, 0}, WHITE);
        staticEntity.texture = LoadTextureFromImage(image);
        staticEntity.hitBox = rightRect;
        UnloadImage(image);

        return staticEntity;
}

void Map::initMap() {
        Vector2 mapSize = {100, 5000};
        StaticEntity rightWall = createStaticEntity({0, 0}, mapSize, LoadImage("../wall.jpg"));
        StaticEntity topWall = createStaticEntity({0, 0}, {mapSize.y, mapSize.x}, LoadImage("../wall.jpg"));
        StaticEntity leftWall = createStaticEntity({mapSize.y, 0}, mapSize, LoadImage("../wall.jpg"));
        StaticEntity bottomWall = createStaticEntity({0, mapSize.y}, {mapSize.y + 100, mapSize.x}, LoadImage("../wall.jpg"));

        

        staticEntities[0] = rightWall;
        staticEntities[1] = topWall;
        staticEntities[2] = leftWall;
        staticEntities[3] = bottomWall;

        Image enemie = LoadImage("../bullet.jpg");
        ImageDrawPixelV(&enemie, {0, 0}, WHITE);
        DynamicEntity* entity = new DynamicEntity({0, 0}, {40, 40}, LoadTextureFromImage(enemie), {50, 50, 100, 100}, 1000, 0);
        UnloadImage(enemie);
        dynamicEntities.push_back(entity);
}

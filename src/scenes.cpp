#include "constants.hpp"
#include <scenes.hpp>

TitleScene::TitleScene() : Scene() { buttonFont = LoadFont(BUTTON_FONT); }

void TitleScene::draw() {
    ClearBackground(BEIGE);
    Vector2 buttonPosition = MeasureTextEx(buttonFont, "Start Game", 40, 4);
    buttonPosition.x = 400 - buttonPosition.x / 2;
    buttonPosition.y = 400 - buttonPosition.y / 2;

    DrawTextEx(buttonFont, "Start Game", buttonPosition, 40, 4,
               {40, 80, 80, 255});
}

void TitleScene::update() {}

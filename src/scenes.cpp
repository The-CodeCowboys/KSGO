#include "scenes.hpp"
#include "button.hpp"
#include <memory>
#include <raylib.h>

TitleScene::TitleScene(SceneManager& sceneManager) : Scene(), _sceneManagaer(sceneManager) {
    buttonFont = GetFontDefault();
    FontStyle buttonFontStyle = {buttonFont, 40, 4, {40, 80, 40, 225}};
    this->_startButton = TextButton{
        {400, 400},
        {"Start Button"},
        buttonFontStyle,
        [&] { this->_sceneManagaer.setScene(std::make_unique<ActualScene>()); },
    };
}

void TitleScene::draw() {
    ClearBackground(BEIGE);

    this->_startButton.draw();
}

void TitleScene::update() { this->_startButton.update(); }

void SceneManager::setScene(std::unique_ptr<Scene> newScene) { this->_currentScene = std::move(newScene); }
Scene& SceneManager::getScene() const { return *this->_currentScene; }

ActualScene::ActualScene() {}
void ActualScene::update() {}
void ActualScene::draw() {
    ClearBackground(BLACK);
    DrawText("SCENE2", 400, 400, 40, RED);
}

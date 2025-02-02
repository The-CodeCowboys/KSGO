#include "scenes.hpp"
#include "button.hpp"
#include "constants.hpp"
#include <functional>
#include <memory>
#include <raylib.h>
#include <string>

TitleScene::TitleScene(SceneManager& sceneManager) : Scene(), _sceneManagaer(sceneManager) {
    buttonFont = GetFontDefault();
    FontStyle buttonFontStyle = {buttonFont, 40, 4, {40, 80, 40, 255}};
    FontStyle buttonHoverFontStyle = buttonFontStyle;
    buttonHoverFontStyle.color = {20, 60, 20, 255};
    this->_startButton = TextButton{
        {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0},
        {"Start Button"},
        buttonFontStyle,
        buttonHoverFontStyle,
        [&] { this->_sceneManagaer.setScene(std::make_unique<GameplayScene>()); },
    };
}

void TitleScene::draw() {
    ClearBackground(BEIGE);

    this->_startButton.draw();
}

void TitleScene::update() { this->_startButton.update(); }

void SceneManager::setScene(std::unique_ptr<Scene> newScene) { this->_currentScene = std::move(newScene); }
Scene& SceneManager::getScene() const { return *this->_currentScene; }

GameplayScene::GameplayScene() : _roundStartTime() {
    this->typingComponent.resetTime();
    this->_currentPhase = GameplayPhase::BUY;
    this->_typingScore = 0;
}

void GameplayScene::update() {
    switch (_currentPhase) {
    case GameplayPhase::BUY:
        this->buyMenuComponent.update();
        break;
    case GameplayPhase::TYPE:
        this->typingComponent.update();
        break;
    case GameplayPhase::FIGHT:
        this->fightingComponent.update();
        break;
    }
}

void GameplayScene::draw() {
    switch (_currentPhase) {
    case GameplayPhase::BUY:
        this->buyMenuComponent.draw();
        break;
    case GameplayPhase::TYPE:
        this->typingComponent.draw();
        break;
    case GameplayPhase::FIGHT:
        this->fightingComponent.draw();
        break;
    }
}

void GameplayScene::setChosenLoadout(Loadout loadout) {
    this->_currentPhase = GameplayPhase::TYPE;
    this->_chosenLoadout = loadout;
}

void GameplayScene::setPlayerTypingScore(int score) {
    this->_currentPhase = GameplayPhase::FIGHT;
    this->_typingScore = score;
}

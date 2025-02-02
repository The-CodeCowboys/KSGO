#pragma once
#include "button.hpp"
#include "components.hpp"
#include "network.hpp"
#include <memory>
#include <raylib.h>

class SceneManager;

enum class GameplayPhase { BUY, TYPE, FIGHT };

class Scene {
    public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Scene() = default;
};

class TitleScene : public Scene {
    public:
    TitleScene(SceneManager& sceneManager);

    void draw() override;

    void update() override;

    private:
    Font buttonFont;
    TextButton _startButton;
    SceneManager& _sceneManagaer;
};

class SceneManager {
    public:
    void setScene(std::unique_ptr<Scene> newScene);
    Scene& getScene() const;

    private:
    std::unique_ptr<Scene> _currentScene;
};

class GameplayScene : public Scene {
    public:
    GameplayScene();

    void draw() override;
    void update() override;

    private:
    void setChosenLoadout(Loadout loadout);
    void setPlayerTypingScore(int score);

    double _roundStartTime;
    GameplayPhase _currentPhase;
    Loadout _chosenLoadout;
    int _typingScore;

    TypingComponent typingComponent{[&](int i) { this->setPlayerTypingScore(i); }};
    BuyMenuComponent buyMenuComponent{[&](Loadout loadout) { setChosenLoadout(loadout); }};
    FightComponent fightingComponent{};
};

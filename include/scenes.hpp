#pragma once
#include "button.hpp"
#include <memory>
#include <raylib.h>

class SceneManager;

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

class ActualScene : public Scene {
    public:
    ActualScene();

    void draw() override;
    void update() override;
};

class SceneManager {
    public:
    void setScene(std::unique_ptr<Scene> newScene);
    Scene& getScene() const;

    private:
    std::unique_ptr<Scene> _currentScene;
};

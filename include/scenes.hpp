#pragma once
#include "button.hpp"
#include "constants.hpp"
#include <functional>
#include <memory>
#include <raylib.h>
#include <string>

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

class SceneManager {
    public:
    void setScene(std::unique_ptr<Scene> newScene);
    Scene& getScene() const;

    private:
    std::unique_ptr<Scene> _currentScene;
};

class Component {
    public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Component() = default;
};

class TypingComponent : public Component {
    public:
    TypingComponent();

    void draw() override;
    void update() override;

    private:
    std::vector<int> _referenceText;
    std::vector<int> _typedText;
    Font _font;
    int _points;

    void updateTextbox();
};

struct LoadoutSpec {
    int baseHealth;
    int baseFireRate;
    int baseAmmo;
    int baseDamage;
    int baseSpeed;
};

struct Loadout {
    void* image;
    std::string title;
    std::string gunName;
    LoadoutSpec attributes;

    static std::array<Loadout, 3> availableLoadouts;
};

class BuyMenuComponent : public Component {
    public:
    BuyMenuComponent(std::function<void(Loadout)> loadoutChosenCallback);

    void draw() override;

    void update() override;

    private:
    std::function<void(Loadout)> _loadoutChosenCallback;
    float _nLoadouts;
    float _sideMargin;
    float _loadoutsGap;
    float _verticalMargin;
    float _loadoutWidth;
    float _borderSize;

    void drawAttributeBar(int x, int y, int nBars, int value, int maxValue, Color filledColor, Color unfilledColor);
    bool isMouseOnLoadout(int i) {
        Rectangle collisionBox = Rectangle{
            _sideMargin + i * (_loadoutWidth + _loadoutsGap) - _borderSize,
            _verticalMargin - _borderSize,
            _loadoutWidth + _borderSize * 2,
            SCREEN_HEIGHT + (_borderSize - _verticalMargin) * 2,
        };

        return CheckCollisionPointRec(GetMousePosition(), collisionBox);
    }
};

class GameplayScene : public Scene {
    public:
    GameplayScene();

    void draw() override;
    void update() override;

    private:
    void setChosenLoadout(Loadout loadout);

    bool _isChoosingLoadout;
    Loadout _chosenLoadout;
    TypingComponent typingComponent{};
    BuyMenuComponent buyMenuComponent{[&](Loadout l) { setChosenLoadout(l); }};
};

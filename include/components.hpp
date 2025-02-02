#pragma once

#include <functional>
#include <raylib.h>
#include <string>

class Component {
    public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Component() = default;
};

class TypingComponent : public Component {
    public:
    TypingComponent(double startingTime, std::function<void(int)> setScoreCallback);

    void draw() override;
    void update() override;

    private:
    std::vector<int> _referenceText;
    std::vector<int> _typedText;
    Font _font;
    int _points;
    int _drawFromColumn;
    double _startingTime;
    std::function<void(int)> _setScoreCallback;

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
    bool isMouseOnLoadout(int i);
};

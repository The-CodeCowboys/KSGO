#pragma once
#include <raylib.h>

class Scene {
    public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual ~Scene() = default;
};

class TitleScene : public Scene {
    public:
    TitleScene();

    void draw() override;

    void update() override;

    private:
    Font buttonFont;
};

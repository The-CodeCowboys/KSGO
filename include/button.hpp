#pragma once
#include <functional>
#include <raylib.h>
#include <string>

struct FontStyle {
    Font font;
    float size;
    float spacing;
    Color color;
};

class TextButton {
    public:
    TextButton();
    TextButton(Vector2 position, std::string text, FontStyle defaultFontStyle, FontStyle fontStyleOnHover,
               std::function<void(void)> onClick);

    void draw();
    void update();

    private:
    Vector2 _position;
    Rectangle _boundingBox;
    std::string _text;
    FontStyle _regularStyle;
    FontStyle _hoverStyle;
    std::function<void(void)> _callback;
};

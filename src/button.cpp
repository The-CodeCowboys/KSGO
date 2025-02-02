#include <button.hpp>
#include <raylib.h>

constexpr int COLLISION_PADDING = 10;
TextButton::TextButton() {}

TextButton::TextButton(Vector2 position, std::string text, FontStyle fontStyle, std::function<void(void)> onClick)
    : _text(text), _fontStyle(fontStyle), _callback(onClick) {
    Vector2 textBoxSize =
        MeasureTextEx(this->_fontStyle.font, this->_text.c_str(), this->_fontStyle.size, this->_fontStyle.spacing);
    Vector2 drawPosition = {position.x - textBoxSize.x / 2, position.y - textBoxSize.y / 2};

    this->_position = drawPosition;
    this->_boundingBox = Rectangle{drawPosition.x - COLLISION_PADDING, drawPosition.y - COLLISION_PADDING,
                                   textBoxSize.x + COLLISION_PADDING * 2, textBoxSize.y + COLLISION_PADDING * 2};
};

void TextButton::draw() {
    DrawTextEx(this->_fontStyle.font, this->_text.c_str(), this->_position, this->_fontStyle.size,
               this->_fontStyle.spacing, this->_fontStyle.color);
    DrawRectangleRec(this->_boundingBox, {0, 0, 0, 155});
}

void TextButton::update() {
    if (CheckCollisionPointRec(GetMousePosition(), this->_boundingBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->_callback();
    }
}

#include <button.hpp>
#include <raylib.h>

constexpr int COLLISION_PADDING = 10;
TextButton::TextButton() {}

TextButton::TextButton(Vector2 position, std::string text, FontStyle defaultStyle, FontStyle hoverStyle,
                       std::function<void(void)> onClick)
    : _text(text), _regularStyle(defaultStyle), _hoverStyle(hoverStyle), _callback(onClick) {
    Vector2 textBoxSize = MeasureTextEx(this->_regularStyle.font, this->_text.c_str(), this->_regularStyle.size,
                                        this->_regularStyle.spacing);
    Vector2 drawPosition = {position.x - textBoxSize.x / 2, position.y - textBoxSize.y / 2};

    this->_position = drawPosition;
    this->_boundingBox = Rectangle{drawPosition.x - COLLISION_PADDING, drawPosition.y - COLLISION_PADDING,
                                   textBoxSize.x + COLLISION_PADDING * 2, textBoxSize.y + COLLISION_PADDING * 2};
};

void TextButton::draw() {
    // DrawRectangleRec(this->_boundingBox, {0, 0, 0, 255}); // Debugging
    FontStyle fontStyle = CheckCollisionPointRec(GetMousePosition(), this->_boundingBox) ? _hoverStyle : _regularStyle;
    DrawTextEx(fontStyle.font, this->_text.c_str(), this->_position, fontStyle.size, fontStyle.spacing,
               fontStyle.color);
}

void TextButton::update() {
    if (CheckCollisionPointRec(GetMousePosition(), this->_boundingBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->_callback();
    }
}

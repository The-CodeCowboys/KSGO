#pragma once
#include <raylib.h>

constexpr char BUTTON_FONT[] = "resources/fonts/button.ttf";

constexpr int SPACE_CODEPOINT = 0x20;
constexpr int CENTER_DOT_CODEPOINT = 0x2022;

constexpr int HEALTH_MAX_SCALE_VALUE = 300;
constexpr int AMMO_MAX_SCALE_VALUE = 30;
constexpr int FIRE_RATE_MAX_SCALE_VALUE = 12;
constexpr int DAMAGE_MAX_SCALE_VALUE = 100;
constexpr int SPEED_MAX_SCALE_VALUE = 40;

namespace TypingConst {
constexpr int BOX_MARGIN = 20;
constexpr int BOX_BORDER_SIZE = 5;
constexpr int PTS_PER_CHAR = 1;
constexpr int PT_LOSS_PER_ERROR = 3;
constexpr Color VALID_CHAR_COLOR = GREEN;
constexpr Color WRONG_CHAR_COLOR = RED;
constexpr Color DEFAULT_CHAR_COLOR = GRAY;
constexpr int ADVANCE_WHEN_REACHING_COLUM_N = 2;
constexpr int FONT_SIZE = 30;
} // namespace TypingConst

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

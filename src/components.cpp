#include "components.hpp"
#include "constants.hpp"
#include <algorithm>

TypingComponent::TypingComponent(double startingTime, std::function<void(int)> setScoreCallback)
    : _startingTime(startingTime), _setScoreCallback(setScoreCallback), _points(0) {
    int length = -1;
    int* codepoints = LoadCodepoints(
        "Le miel devient de l'air, généralement au lever des astres, et principalement sous la constellation de "
        "Sirius, jamais avant le lever des Pléiades, vers l'aube du jour ; aussi, à la naissance de l'aurore, les "
        "feuilles des arbres sont-elles alors humectées de miel ; et ceux qui se trouventle matin dans les champs "
        "sentent leurs habits et leurs cheveux enduits d'une liqueur onctueuse."
        "Le miel devient de l'air, généralement au lever des astres, et principalement sous la constellation de "
        "Sirius, jamais avant le lever des Pléiades, vers l'aube du jour ; aussi, à la naissance de l'aurore, les "
        "feuilles des arbres sont-elles alors humectées de miel ; et ceux qui se trouventle matin dans les champs "
        "sentent leurs habits et leurs cheveux enduits d'une liqueur onctueuse.",
        &length);

    _referenceText = {codepoints, codepoints + length};
    _typedText = {};
    _font = LoadFontEx(BUTTON_FONT, TypingConst::FONT_SIZE, nullptr, 0x3000);
    _drawFromColumn = 0;
}

void TypingComponent::draw() {
    ClearBackground(BLACK);

    DrawRectangle(TypingConst::BOX_MARGIN - TypingConst::BOX_BORDER_SIZE,
                  (SCREEN_HEIGHT - TypingConst::BOX_MARGIN) / 2 - TypingConst::BOX_BORDER_SIZE,
                  SCREEN_WIDTH + 2 * (TypingConst::BOX_BORDER_SIZE - TypingConst::BOX_MARGIN),
                  ((SCREEN_HEIGHT - TypingConst::BOX_MARGIN) / 2 + 2 * TypingConst::BOX_BORDER_SIZE), GRAY);

    DrawRectangle(TypingConst::BOX_MARGIN, (SCREEN_HEIGHT - TypingConst::BOX_MARGIN) / 2,
                  SCREEN_WIDTH - 2 * TypingConst::BOX_MARGIN, ((SCREEN_HEIGHT - TypingConst::BOX_MARGIN) / 2), WHITE);

    float x = TypingConst::BOX_MARGIN * 2;
    float y = (SCREEN_HEIGHT - TypingConst::BOX_MARGIN) / 2.0 + TypingConst::BOX_MARGIN;

    int score = 0;
    int currentColumn = 0;

    for (int i = 0; i < _referenceText.size(); i++) {
        Color textColor = BLUE;
        int codepoint = _referenceText[i];

        if (i < _typedText.size()) {
            if (codepoint == _typedText[i]) {
                score += TypingConst::PTS_PER_CHAR;
                textColor = TypingConst::VALID_CHAR_COLOR;
            } else {
                score -= TypingConst::PT_LOSS_PER_ERROR;
                textColor = TypingConst::WRONG_CHAR_COLOR;
            }
        } else {
            if (i == _typedText.size() &&
                currentColumn == TypingConst::ADVANCE_WHEN_REACHING_COLUM_N + _drawFromColumn) {
                _drawFromColumn++;
            }
            textColor = TypingConst::DEFAULT_CHAR_COLOR;
        }

        if (codepoint == SPACE_CODEPOINT) {
            x += 5;
            if (currentColumn >= _drawFromColumn) {
                codepoint = CENTER_DOT_CODEPOINT;
                DrawTextCodepoint(_font, codepoint, {x, y}, TypingConst::FONT_SIZE, textColor);
            }
            x += 5;
        } else if (currentColumn >= _drawFromColumn) {
            DrawTextCodepoint(_font, codepoint, {x, y}, TypingConst::FONT_SIZE, textColor);
        }

        GlyphInfo glyph = GetGlyphInfo(_font, codepoint);
        x += 2 + glyph.advanceX;
        if (x > SCREEN_WIDTH - TypingConst::FONT_SIZE * 2) {
            if (currentColumn >= _drawFromColumn) {
                y += TypingConst::FONT_SIZE;
            }
            x = TypingConst::BOX_MARGIN * 2;
            currentColumn++;
        }

        if (y > SCREEN_HEIGHT - TypingConst::BOX_MARGIN - TypingConst::FONT_SIZE - TypingConst::BOX_BORDER_SIZE) {
            break;
        }
    }

    this->_points = std::max(0, score);
}

void TypingComponent::update() {
    this->updateTextbox();
    if (GetTime() - this->_startingTime > 30) {
        this->_setScoreCallback(this->_points);
    }
}

void TypingComponent::updateTextbox() {
    int utf8Codepoint = GetCharPressed();

    if (utf8Codepoint != 0) {
        _typedText.push_back(utf8Codepoint);
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        int lastPos = _typedText.size() - 1;

        if (_referenceText[lastPos] == SPACE_CODEPOINT) {
            bool lastWordCorrect = true;
            for (int i = lastPos - 1; i > 0 && _referenceText[i] != SPACE_CODEPOINT; i--) {
                if (_typedText[i] != _referenceText[i]) {
                    lastWordCorrect = false;
                    break;
                }
            }

            if (!lastWordCorrect) {
                _typedText.pop_back();
            }

        } else if (!_typedText.empty()) {
            _typedText.pop_back();
        }
    }
}

std::array<Loadout, 3> Loadout::availableLoadouts = {
    Loadout{
        nullptr,
        "Specialist",
        "Sniper",
        LoadoutSpec{
            100,
            2,
            3,
            100,
            20,
        },
    },
    Loadout{
        nullptr,
        "Brute",
        "Shotgun",
        LoadoutSpec{
            300,
            5,
            20,
            50,
            20,
        },
    },
    Loadout{
        nullptr,
        "Corp",
        "Assault Rifle",
        LoadoutSpec{
            200,
            10,
            25,
            40,
            20,
        },
    },
};

BuyMenuComponent::BuyMenuComponent(std::function<void(Loadout)> loadoutChosenCallback)
    : _loadoutChosenCallback(loadoutChosenCallback) {
    this->_sideMargin = 30;
    this->_verticalMargin = 40;
    this->_nLoadouts = Loadout::availableLoadouts.size();
    this->_loadoutsGap = 20;
    this->_borderSize = _loadoutsGap / 4;

    this->_loadoutWidth = (static_cast<float>(SCREEN_WIDTH) - 2.0 * _sideMargin - (_nLoadouts - 1) * _loadoutsGap) /
                          static_cast<float>(_nLoadouts);
}

struct AttributeDrawingData {
    std::string name;
    int maxValue;
    Color filledColor;
    Color unfilledColor;
    std::function<int(LoadoutSpec)> getValueFromLoadout;
};

std::array<AttributeDrawingData, 5> attributeDrawingData = {{
    {
        "Health",
        HEALTH_MAX_SCALE_VALUE,
        GREEN,
        LIGHTGRAY,
        [](LoadoutSpec spec) { return spec.baseHealth; },
    },
    {
        "Ammo",
        AMMO_MAX_SCALE_VALUE,
        BLUE,
        LIGHTGRAY,
        [](LoadoutSpec spec) { return spec.baseAmmo; },
    },
    {
        "Fire Rate",
        FIRE_RATE_MAX_SCALE_VALUE,
        BLUE,
        LIGHTGRAY,
        [](LoadoutSpec spec) { return spec.baseFireRate; },
    },
    {
        "Damage",
        DAMAGE_MAX_SCALE_VALUE,
        RED,
        LIGHTGRAY,
        [](LoadoutSpec spec) { return spec.baseDamage; },
    },
    {
        "Speed",
        SPEED_MAX_SCALE_VALUE,
        PURPLE,
        LIGHTGRAY,
        [](LoadoutSpec spec) { return spec.baseSpeed; },
    },
}};

void BuyMenuComponent::draw() {
    ClearBackground(BLACK);
    int x = _sideMargin;
    for (int i = 0; i < _nLoadouts; i++) {
        int y = _verticalMargin;
        Color borderColor = GRAY;

        int borderSize = _borderSize;

        if (isMouseOnLoadout(i)) {
            borderSize *= 2;
            borderColor = BLUE;
        }

        DrawRectangle(x - borderSize, y - borderSize, _loadoutWidth + borderSize * 2,
                      SCREEN_HEIGHT + (borderSize - _verticalMargin) * 2, borderColor);

        DrawRectangle(x, y, _loadoutWidth, SCREEN_HEIGHT - _verticalMargin * 2, WHITE);

        int insideX = x + _sideMargin;

        Loadout currentLoadout = Loadout::availableLoadouts[i];
        y += 20;
        DrawText(currentLoadout.title.c_str(), insideX, y, 35, BLACK);
        y += 35;
        DrawText(currentLoadout.gunName.c_str(), insideX, y, 30, GRAY);

        y += 60;

        for (AttributeDrawingData drawingData : attributeDrawingData) {
            y += 60;
            DrawText(drawingData.name.c_str(), insideX, y, 24, GRAY);
            y += 30;
            drawAttributeBar(x, y, 5, drawingData.getValueFromLoadout(currentLoadout.attributes), drawingData.maxValue,
                             drawingData.filledColor, drawingData.unfilledColor);
        }

        x += _loadoutWidth + _loadoutsGap;
    }
}

void BuyMenuComponent::drawAttributeBar(int x, int y, int nBars, int value, int maxValue, Color filledColor,
                                        Color unfilledColor) {
    int attributeBarGap = 5;
    int width = (_loadoutWidth - 2.0 * _sideMargin - (nBars - 1) * attributeBarGap) / static_cast<float>(nBars);
    int nBarsFilled = static_cast<float>(value) * nBars / static_cast<float>(maxValue);
    nBarsFilled = std::clamp(nBarsFilled, 1, nBars);

    for (int i = 0; i < nBars; i++) {
        DrawRectangle(x + _sideMargin, y, width, 16, i < nBarsFilled ? filledColor : unfilledColor);
        x += width + attributeBarGap;
    }

    x += _loadoutWidth + _loadoutsGap;
}

void BuyMenuComponent::update() {

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < _nLoadouts; i++) {
            if (isMouseOnLoadout(i)) {
                _loadoutChosenCallback(Loadout::availableLoadouts[i]);
            }
        }
    }
}

bool BuyMenuComponent::isMouseOnLoadout(int i) {
    Rectangle collisionBox = Rectangle{
        _sideMargin + i * (_loadoutWidth + _loadoutsGap) - _borderSize,
        _verticalMargin - _borderSize,
        _loadoutWidth + _borderSize * 2,

        SCREEN_HEIGHT + (_borderSize - _verticalMargin) * 2,
    };

    return CheckCollisionPointRec(GetMousePosition(), collisionBox);
};

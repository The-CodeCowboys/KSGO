
#include "StaticEntity.hpp"

void StaticEntity::render() {
    DrawTextureV(this->texture, this->position, WHITE);
}

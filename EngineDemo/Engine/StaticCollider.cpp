#include "StaticCollider.h"

namespace Engine
{
    StaticCollider::StaticCollider
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar
    ) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
    {
        canMove = false;
    }
}
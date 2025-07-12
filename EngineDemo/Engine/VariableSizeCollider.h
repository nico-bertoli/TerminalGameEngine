#pragma once
#include "Collider.h"

namespace Engine
{
    class VariableSizeCollider : public Collider
    {
        //---------------------------------------------------------- Fields
        char modelChar;
        size_t modelSizeX;
        size_t modelSizeY;
        Model model;
        //---------------------------------------------------------- Methods
    public:
        VariableSizeCollider
        (
            int xPos,
            int yPos,
            size_t modelSizeX,
            size_t modelSizeY,
            char modelChar
        ) :
            Collider(xPos, yPos),
            modelSizeX(modelSizeX),
            modelSizeY(modelSizeY),
            modelChar(modelChar)
        {
            model = CreteModelUsingChar(modelChar, modelSizeX, modelSizeY);
        }

    protected:
        void InitModel() override { SetModel(model); }
    };
}
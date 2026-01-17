#pragma once
#include "Config.h"
#include "SimEntities/VariableSizeCollider.h"

namespace Engine
{
    class StaticCollider : public VariableSizeCollider
    {
        //---------------------------------------------------------- Methods
    public:
        StaticCollider
        (
            int x_pos,
            int y_pos,
            size_t size_x,
            size_t size_y,
            char model_char
        );

        bool CanExitScreenSpace() const override { return true; }
        double GetGravityScale() const override { return 0; }
    };
}
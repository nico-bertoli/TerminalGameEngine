#pragma once
#include <terme/config.h>
#include <terme/sim_entities/variable_size_collider.h>

namespace terme
{
    class static_collider : public variable_size_collider
    {
        //---------------------------------------------------------- Methods
    public:
        static_collider
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
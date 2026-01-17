#pragma once
#include <terme/sim_entities/collider.h>

namespace terme
{
    class variable_size_collider : public Collider
    {
        //---------------------------------------------------------- Fields
        char model_char_;
        size_t model_size_x_;
        size_t model_size_y_;
        Model model_;
        //---------------------------------------------------------- Methods
    public:
        variable_size_collider
        (
            int x_pos,
            int y_pos,
            size_t model_size_x,
            size_t model_size_y,
            char model_char
        ) :
            Collider(x_pos, y_pos),
            model_size_x_(model_size_x),
            model_size_y_(model_size_y),
            model_char_(model_char)
        {
            model_ = CreteModelUsingChar(model_char, model_size_x, model_size_y);
        }

    protected:
        void InitModel() override { SetModel(model_); }
    };
}
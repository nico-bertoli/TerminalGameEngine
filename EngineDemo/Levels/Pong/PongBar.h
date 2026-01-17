#pragma once
#include "SimEntities/VariableSizeCollider.h"

namespace Pong
{
    class PongBar : public Engine::VariableSizeCollider
    {
        //---------------------------------------------------------- Fields
    private:
        double move_speed_;
        bool is_bottom_bar_;
        double deflect_ball_factor_;

        //---------------------------------------------------------- Methods
    public:
        PongBar
        (
            int x_pos,
            int y_pos,
            size_t size_x,
            size_t size_y,
            char model_char,
            double move_speed,
            double deflect_ball_factor,
            bool is_bottom_bar
        );

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::color::kCyan; }

        double GetDeflectBallFactor() { return deflect_ball_factor_; }

    protected:
        void Update() override;
    };
}
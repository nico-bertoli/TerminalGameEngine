#pragma once
#include "SimEntities/Collider.h"
#include "General/Vector2Int.h"

namespace Platformer
{
    class PressurePlate : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    public:
        nbase_kit::Event<> on_press;
        nbase_kit::Event<> on_release;

    private:
        Engine::Model pressed_model_;
        Engine::Model unpressed_model_;

        //---------------------------------------------------------- Methods
    public:
        PressurePlate(int x_pos, int y_pos, size_t width);

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::color::kCyan; }

    protected:
        void OnCollisionEnter(std::shared_ptr<Engine::Collider> other, Engine::Direction collision_dir) override;
        void OnCollisionExit(Engine::Direction ending_collision_dir) override;
        void InitModel() override { SetModel(unpressed_model_); }
    };
}
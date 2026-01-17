#pragma once
#include "Config.h"
#include "SimEntities/VariableSizeCollider.h"

namespace Platformer
{

    class AutomaticDoor : public Engine::VariableSizeCollider
    {
        //---------------------------------------------------------- Fields
    private:
        double move_speed_;
        int starting_pos_y_;
        int energy_sources_counter_ = 0;

        //---------------------------------------------------------- Methods
    public:
        AutomaticDoor
        (
            int x_pos,
            int y_pos,
            size_t size_x,
            size_t size_y,
            char model_char,
            double move_speed
        );

        bool IsOpen() const { return energy_sources_counter_ > 0; }
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const { return Engine::color::kCyan; }
        void AddEnergySource() { ++energy_sources_counter_; }
        void RemoveEnergySource();

    protected:
        void Update() override;
    };
}
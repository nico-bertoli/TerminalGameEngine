#pragma once
#include "SimEntities/Collider.h"
#include "General/Vector2Int.h"

namespace Engine {class Level;}

namespace Platformer
{
    class LevelEndFlag : public Engine::Collider
    {
        //---------------------------------------------------------- Fieldds

    public:
        nbase_kit::Event<> OnTouchBunny;

    private:
        static inline const Engine::Model kFlagModel = Engine::Model
        (
            2,
            {
                '|','\\',
                '|','/',
                '|',' '
            }
        );
        Engine::Level* level_;

        //---------------------------------------------------------- Methods
    public:
        LevelEndFlag(Engine::Level* level, int x_pos, int y_pos);
        Engine::TerminalColor GetColor() const override { return Engine::color::kGreen; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override;
        void InitModel() override { SetModel(kFlagModel); }
    };
}
#pragma once
#include "SimEntities/Collider.h"	
#include "General/Vector2Int.h"

namespace Pong
{
    class PongBar;
    class PongLevel;

    class PongBall : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    public:
        nbase_kit::Event<> on_goal;
    private:
        PongLevel* level_;
        double y_speed_;
        double x_speed_;
        bool is_first_launch_;
        static inline const Engine::Model kModel = Engine::Model(1, { '@' });

        //---------------------------------------------------------- Methods
    public:
        PongBall(PongLevel* level, int x_pos, int y_pos, double y_speed);
        Engine::TerminalColor GetColor() const override { return Engine::color::kGreen; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override;
        void Update() override;
        void InitModel() override { SetModel(kModel); }

    private:
        void HandleBarCollision(std::shared_ptr<PongBar> colliding_bar);
    };
}
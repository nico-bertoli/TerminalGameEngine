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
        Event<> OnGoal;
    private:
        PongLevel* level;
        double ySpeed;
        double xSpeed;
        bool iSFirstLaunch;
        static const Engine::Model MODEL;

        //---------------------------------------------------------- Methods
    public:
        PongBall(PongLevel* level, int xPos, int yPos, double ySpeed);
        Engine::TerminalColor GetColor() const override { return Engine::Color::GREEN; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
        void Update() override;
        void InitModel() override { SetModel(MODEL); }

    private:
        void HandleBarCollision(std::shared_ptr<PongBar> collidingBar);
    };
}


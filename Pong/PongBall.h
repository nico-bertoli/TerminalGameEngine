#pragma once
#include "Collider.h"	
#include "Event.h"

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
        int GetColor() const override { return Engine::Terminal::GREEN; }

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


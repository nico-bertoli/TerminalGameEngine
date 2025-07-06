#pragma once
#include "Collider.h"
#include "Event.h"

namespace Engine {class Level;}

namespace Platformer
{
    class LevelEndFlag : public Engine::Collider
    {
        //---------------------------------------------------------- Fieldds

    public:
        Event<> OnTouchBunny;

    private:
        static const Engine::Model flagModel;
        Engine::Level* level;

        //---------------------------------------------------------- Methods
    public:
        LevelEndFlag(Engine::Level* level, int xPos, int yPos);
        int GetColor() const override { return Engine::Terminal::GREEN; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
        void InitModel() override { SetModel(flagModel); }
    };
}
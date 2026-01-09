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
        NbaseKit::Event<> OnTouchBunny;

    private:
        static const Engine::Model flagModel;
        Engine::Level* level;

        //---------------------------------------------------------- Methods
    public:
        LevelEndFlag(Engine::Level* level, int xPos, int yPos);
        Engine::TerminalColor GetColor() const override { return Engine::Color::GREEN; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
        void InitModel() override { SetModel(flagModel); }
    };
}
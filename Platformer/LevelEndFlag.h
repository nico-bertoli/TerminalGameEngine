#pragma once
#include "Collider.h"
#include "Event.h"

namespace Engine {class Level;}

namespace Platformer
{
    //class Engine::Level;
    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using Direction = Engine::Direction;
    using Level = Engine::Level;

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
        LevelEndFlag(Level* level, int xPos, int yPos);
        int GetColor() const override { return Engine::Terminal::GREEN; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) override;
        void InitModel() override { SetModel(flagModel); }
    };
}
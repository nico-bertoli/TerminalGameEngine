#pragma once
#include "Collider.h"
#include "Event.h"

namespace Platformer
{
    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using Direction = Engine::Direction;

    class PressurePlate : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    public:
        Event<> OnPress;
        Event<> OnRelease;

    private:
        Engine::Model pressedModel;
        Engine::Model unpressedModel;

        //---------------------------------------------------------- Methods
    public:
        PressurePlate(int xPos, int yPos, size_t width);

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        int GetColor() const override { return Engine::Terminal::CYAN; }

    protected:
        void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) override;
        void OnCollisionExit(Direction endingCollisionDir) override;
        void InitModel() override { SetModel(unpressedModel); }
    };
}
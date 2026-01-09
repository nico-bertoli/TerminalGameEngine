#pragma once
#include "SimEntities/Collider.h"
#include "General/Vector2Int.h"

namespace Platformer
{
    class PressurePlate : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    public:
        NbaseKit::Event<> OnPress;
        NbaseKit::Event<> OnRelease;

    private:
        Engine::Model pressedModel;
        Engine::Model unpressedModel;

        //---------------------------------------------------------- Methods
    public:
        PressurePlate(int xPos, int yPos, size_t width);

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::Color::CYAN; }

    protected:
        void OnCollisionEnter(std::shared_ptr<Engine::Collider> other, Engine::Direction collisionDir) override;
        void OnCollisionExit(Engine::Direction endingCollisionDir) override;
        void InitModel() override { SetModel(unpressedModel); }
    };
}
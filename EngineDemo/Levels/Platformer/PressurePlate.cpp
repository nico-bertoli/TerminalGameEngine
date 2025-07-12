#include "PressurePlate.h"
#include "AudioManager.h"

using std::shared_ptr;
using Direction = Engine::Direction;

namespace Platformer
{
    PressurePlate::PressurePlate(int xPos, int yPos, size_t width) : Collider(xPos, yPos)
    {
        unpressedModel = CreteModelUsingChar('=', width, 1);
        pressedModel = CreteModelUsingChar('_', width, 1);
    }

    void PressurePlate::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
    {
        if (collisionDir == Direction::up && collisions[Direction::up].size() == 1)
        {
            OnPress.Notify();
            SetModel(pressedModel);
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ButtonPress.wav");
        }
    }

    void PressurePlate::OnCollisionExit(Direction endingCollisionDir)
    {
        if (endingCollisionDir == Direction::up && collisions[Direction::up].size() == 0)
        {
            OnRelease.Notify();
            SetModel(unpressedModel);
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ButtonRelease.wav");
        }

    }
}
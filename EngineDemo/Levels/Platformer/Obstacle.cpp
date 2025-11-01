#include "Obstacle.h"
#include "Managers/AudioManager.h"
#include "Managers/TimeManager.h"

using std::shared_ptr;
using Engine::Model;
using Engine::Direction;

namespace Platformer
{
    Model Obstacle::model = {};

    void Obstacle::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
    {
        Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/Hit.wav", 0.2);
    }

    void Obstacle::InitModel()
    {
        if (model.GetSizeY() == 0)
            model = CreteModelUsingChar(-37, size_t(4), size_t(2));
        SetModel(model);
    }

}
#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

using Engine::Model;
using Engine::Direction;
using Engine::Level;
using std::shared_ptr;


namespace Platformer
{
    const Model LevelEndFlag::flagModel
    (
        2,
        {
            '|','\\',
            '|','/',
            '|',' '
        }
    );

    LevelEndFlag::LevelEndFlag(Level* level, int xPos, int yPos) : Collider(xPos, yPos), level(level) {}

    void LevelEndFlag::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
    {
        if(std::static_pointer_cast<Bunny>(other))
            OnTouchBunny.Notify();
    }
}
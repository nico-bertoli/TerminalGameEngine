#include "LevelEndFlag.h"
#include "Bunny.h"
#include "SimEntities/Level.h"

using Engine::Model;
using Engine::Direction;
using Engine::Level;
using std::shared_ptr;

namespace Platformer
{
    const Model LevelEndFlag::flag_model_
    (
        2,
        {
            '|','\\',
            '|','/',
            '|',' '
        }
    );

    LevelEndFlag::LevelEndFlag(Level* level, int x_pos, int y_pos) : Collider(x_pos, y_pos), level_(level) {}

    void LevelEndFlag::OnCollisionEnter(shared_ptr<Collider> other, Direction collision_dir)
    {
        if(std::static_pointer_cast<Bunny>(other))
            OnTouchBunny.Notify();
    }
}
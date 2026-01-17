#include <terme/sim_entities/static_collider.h>

namespace terme
{
    static_collider::static_collider
    (
        int x_pos,
        int y_pos,
        size_t size_x,
        size_t size_y,
        char model_char
    ) : variable_size_collider(x_pos, y_pos, size_x, size_y, model_char)
    {
        can_move_ = false;
    }
}
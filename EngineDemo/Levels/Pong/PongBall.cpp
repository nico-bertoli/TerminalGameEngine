#include "PongBall.h"
#include "PongBar.h"
#include "Core/Simulation.h"
#include "Managers/AudioManager.h"
#include "PongLevel.h"
#include "Utils/RandomUtils.h"

using Engine::Model;
using std::shared_ptr;
using Engine::Direction;

namespace Pong
{
    const Model PongBall::MODEL(1, { '@' });

    PongBall::PongBall(PongLevel* level, int x_pos, int y_pos, double y_speed)
        :
        Collider(x_pos, y_pos),
        level_(level),
        y_speed_(y_speed)
    {
        x_speed_ = 0;
        is_first_launch_ = true;

        if (RandomUtils::GetRandomInt(0, 1) == 1)
            this->y_speed_ = -y_speed;
    }

    void PongBall::OnCollisionEnter(shared_ptr<Collider> other, Direction collision_dir)
    {
        is_first_launch_ = false;

        if (GetPosY() == level_->GetWorldSizeY() - level_->GetScreenPadding() - 1)
        {
            level_->IncreaseP1Score();
            on_goal.Notify();
            return;
        }


        if (GetPosY() == level_->GetScreenPadding())
        {
            level_->IncreaseP2Score();
            on_goal.Notify();
            return;
        }

        Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Pong/BallHit1.wav", 0.02);

        if (collision_dir == Direction::kUp || collision_dir == Direction::kDown)
        {
            y_speed_ = -y_speed_;
            
            shared_ptr<PongBar> collider_bar = std::dynamic_pointer_cast<PongBar>(other);
            if (collider_bar != nullptr)
                HandleBarCollision(collider_bar);
        }
        else
        {
            x_speed_ = -x_speed_;
        }
    }

    void PongBall::HandleBarCollision(shared_ptr<PongBar> colliding_bar)
    {
        int other_mid_x = (colliding_bar->GetMaxPosX() + colliding_bar->GetPosX()) / 2;
        int distance_from_mid_point = GetPosX() - other_mid_x;

        if (distance_from_mid_point <= 0)
            distance_from_mid_point -= 1;

        int original_sign = distance_from_mid_point > 0 ? 1 : -1;
        x_speed_ = std::pow(std::abs(distance_from_mid_point), colliding_bar->GetDeflectBallFactor());
        x_speed_ *= original_sign;
    }

    void PongBall::Update()
    {
        if (level_->IsGameOver())
            return;

        Collider::Update();

        if (x_speed_ > 0)
            TryMove(Direction::kRight, x_speed_);
        else if (x_speed_ < 0)
            TryMove(Direction::kLeft, x_speed_);

        if (y_speed_ > 0)
            TryMove(Direction::kUp, y_speed_);
        else if (y_speed_ < 0)
            TryMove(Direction::kDown, y_speed_);
    }
}
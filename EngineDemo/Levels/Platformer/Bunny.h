#pragma once
#include "Config.h"
#include "SimEntities/Collider.h"
#include "General/Vector2Int.h"
#include <string>

namespace Platformer
{
    class Bunny : public Engine::Collider
    {
        enum class State
        {
            kIdle,
            kWalking,
            kJumpingUp,
            kJumpingDown,
            kDefeated
        };

        //---------------------------------------------------------- Model
    private:
        static constexpr char kCharNose = '.';
        static constexpr char kCharEye = 'O';
        static constexpr char kCharGameoverEye = '*';
        static constexpr char kCharChest = ':';
        static constexpr char kCharFootUp = '@';

        //todo make this iniline constexpr and init them directly in header
        static const Engine::Model kModelWalkLeft;
        static const Engine::Model kModelWalkRight;
        static const Engine::Model kModelJumpRight;
        static const Engine::Model kModelJumpLeft;
        static const Engine::Model kModelDefeated;
        static const Engine::Model kModelIdleRight;
        static const Engine::Model kModelIdleLeft;

        //---------------------------------------------------------- Settings
    private:
        static constexpr size_t kJumpHeight = 10;
        static constexpr double kMoveUpSpeed = 24;
        static constexpr double kMoveDownSpeed = 24;
        static constexpr double kMoveDownControlledSpeed = 8;
        static constexpr double kSideMovementSpeed = 24;
        static constexpr double kStepAnimEverySeconds = 0.7f;

        //---------------------------------------------------------- Fields
    public:
        nbase_kit::Event<> on_obstacle_hit;
    private:
        State state;
        double last_time_moved_on_x_ = 0;
        int previous_position_x_;
        int jump_starting_y_ = -1;

        Engine::Model active_model_jump_;
        Engine::Model active_model_idle_;
        Engine::Model active_model_walk_;
        //---------------------------------------------------------- Methods
    public:
        Bunny(int x_pos, int y_pos);

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override;
        Engine::TerminalColor GetColor() const override { return Engine::color::kGreen; }

    protected:
        void Update() override;
        void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override;
        void InitModel() override { SetModel(kModelIdleLeft); }

    private:
        bool IsJumping() const { return state == State::kJumpingDown || state == State::kJumpingUp; }
        void SetState(State new_state);
        void UpdateModel();
        void SwitchWalkIdleState();
        void HandleVerticalMovement();
        void HandleHorizontalMovement();
        void HandleSounds(State old_state, State new_state);
        bool IsTouchingGround() { return collisions_[Engine::Direction::kDown].size() > 0; }
        bool IsJumping() { return state == State::kJumpingDown || state == State::kJumpingUp; }
        void ActivateLeftModels(bool activate);
        void OnMoveCallback(Engine::Direction dir);
    };
}
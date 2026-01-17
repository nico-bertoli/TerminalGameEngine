#pragma once
#include "Config.h"
#include "SimEntities/Collider.h"

namespace SpaceInvaders
{
    class SpaceInvadersLevel;

    class PlayerTank : public Engine::Collider
    {
        //---------------------------------------------------------- Settings
    public:
        static constexpr double kMoveSpeed = 24;
        static constexpr double kProjectileSpeed = 32;
        static constexpr double kShotsDelay = 0.3;
        static constexpr size_t kMaxHealth = 3;

        //---------------------------------------------------------- Fields
    public:
        nbase_kit::Event<size_t> on_damage_taken;

    private:
        static inline const Engine::Model kModel = Engine::Model
        (
            5,
            {
                ' ', '_', '^', '_', ' ',
                '/', '_', '_', '_', '\\'
            }
        );
        SpaceInvadersLevel* level_;
        double last_time_shot_ = -1;
        size_t health_ = kMaxHealth;

        //---------------------------------------------------------- Methods
    public:
        PlayerTank(int x_pos, int y_pos, SpaceInvadersLevel* level) : Collider(x_pos, y_pos), level_(level) {};

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        Engine::TerminalColor GetColor() const override { return Engine::color::kGreen; }
        void InitModel() override { SetModel(kModel); }
        void HandleMovement();
        void HandleShooting();
        void TakeDamage();
        size_t GetHealth() { return health_; }

    protected:
        void Update() override;
    };

}
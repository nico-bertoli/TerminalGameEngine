#pragma once
#include "Config.h"
#include "Collider.h"

namespace SpaceInvaders
{
    class SpaceInvadersLevel;

    class PlayerTank : public Engine::Collider
    {
        //---------------------------------------------------------- Settings
    public:
        static double constexpr MOVE_SPEED = 24;
        static double constexpr PROJECTILE_SPEED = 32;
        static double constexpr SHOTS_DELAY = 0.3;
        static size_t const MAX_HEALTH = 3;

        //---------------------------------------------------------- Fields
    public:
        Event<size_t> OnDamageTaken;

    private:
        static const Engine::Model MODEL;
        SpaceInvadersLevel* level;
        double lastTimeShot = -1;
        size_t health = MAX_HEALTH;

        //---------------------------------------------------------- Methods
    public:
        PlayerTank(int xPos, int yPos, SpaceInvadersLevel* level) : Collider(xPos, yPos), level(level) {};

        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        int GetColor() const override { return Engine::Terminal::GREEN; }
        void InitModel() override { SetModel(MODEL); }
        void HandleMovement();
        void HandleShooting();
        void TakeDamage();
        size_t GetHealth() { return health; }

    protected:
        void Update() override;
    };

}
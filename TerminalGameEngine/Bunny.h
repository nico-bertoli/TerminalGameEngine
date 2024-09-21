#pragma once

#include "Config.h"
#include "CollidingObject.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "TimeHelper.h"
#include "Obstacle.h"
#include "Simulation.h"
#include "TerminalUtils.h"

#include <string>

class Level;

class Bunny : public CollidingObject
{
    enum class State
    {
        idle,
        walking,
        jumpingUp,
        jumpingDown,
        defeated
    };
    
//---------------------------------------------------------- Model
private:
    static const char NOSE_CHAR = '.';
    static const char EYE_CHAR = 'O';
    static const char GAMEOVER_EYE_CHAR = '*';
    static const char CHEST_CHAR = ':';

    static const std::vector<std::vector<char>> walkLeftModel;
    static const std::vector<std::vector<char>> walkRightModel;
    static const std::vector<std::vector<char>> jumpRightModel;
    static const std::vector<std::vector<char>> jumpLeftModel;
    static const std::vector<std::vector<char>> defeatedModel;
    static const std::vector<std::vector<char>> idleModelRight;
    static const std::vector<std::vector<char>> idleModelLeft;

    Level* level;

//---------------------------------------------------------- Fields

    static const uint JUMP_HEIGHT = 10;
    static constexpr float MOVE_UP_SPEED = 3;
    static constexpr float MOVE_DOWN_SPEED = 3;
    static constexpr float MOVE_DOWN_CONTROLLED_SPEED = 0.8;
    static constexpr float SIDE_MOVEMENT_SPEED = 3.0;
    static constexpr float STEP_ANIM_EVERY_SECONDS = 0.7f;

    State state;
    float lastTimeMovedOnX = 0;
    int previousPositionX;
    int jumpStartingY = -1;

//---------------------------------------------------------- Methods
public:
    Bunny(int xPos, int yPos, Level* level);

    void Update() override;
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override;
    virtual int GetColor() const { return TerminalUtils::GREEN; }

protected:
    virtual void Move(Direction direction, float moveSpeed) override;
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) override {}

private:
    std::vector<std::vector<char>> jumpingModel;
    std::vector<std::vector<char>> idleModel;
    std::vector<std::vector<char>> walkingModel;

    bool IsJumping() const { return state == State::jumpingDown || state == State::jumpingUp; }
    void SetState(State newState);
    void UpdateModel();
    void HandleIdleWalkState();
    void HandleVerticalMovement();
    void HandleHorizontalMovement();
    void HandleSounds(State oldState, State newState);
    bool IsTouchingGround() { return collidingDirections[static_cast<int>(Direction::down)]; }
    bool IsJumping() { return state == State::jumpingDown || state == State::jumpingUp; }

#pragma endregion Methods
};
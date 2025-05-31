#include "Bunny.h"
#include "Level.h"
#include "InputUtils.h"
#include "TimeHelper.h"
#include "AudioManager.h"
#include "Simulation.h"
#include "Obstacle.h"

using Engine::Model;
using Engine::Direction;
using std::weak_ptr;

namespace Platformer
{
    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using namespace Engine::InputUtils;

    //---------------------------------------------------------- Models
    const Model Bunny::MODEL_WALK_LEFT
    (
        5,
        {
            '(',  92, '(',  92, ' ' ,
            '(', CHAR_EYE, CHAR_NOSE, CHAR_EYE, ')',
            '/', -36, CHAR_CHEST, '_', '|'
        }
    );


    const Model Bunny::MODEL_WALK_RIGHT
    (
        5,
        {
            ' ', '/', ')', '/', ')' ,
            '(', CHAR_EYE, CHAR_NOSE, CHAR_EYE, ')' ,
            '|', '_', CHAR_CHEST, -36, 92
        }
    );


    const Model Bunny::MODEL_JUMP_RIGHT
    (
        5,
        {
            ' ', '/', ')', '/', ')' ,
             '(', CHAR_EYE, CHAR_NOSE, CHAR_EYE, ')' ,
             92, -36, CHAR_CHEST, -36, '/'
        }
    );

    const Model Bunny::MODEL_JUMP_LEFT
    (
        5,
        {
            '(', 92, '(', 92, ' ',
            '(', CHAR_EYE, CHAR_NOSE, CHAR_EYE, ')',
            92, -36, CHAR_CHEST, -36, '/'
        }
    );

    const Model Bunny::MODEL_DEFEATED
    (
        5,
        {
            ' ', '/', ')', '/', ')',
            '(', CHAR_GAMEOVER_EYE, CHAR_NOSE, CHAR_GAMEOVER_EYE, ')',
            '|', -36, CHAR_CHEST, -36, '|'
        }
    );

    const Model Bunny::MODEL_IDLE_RIGHT
    (
        5,
        {
            ' ', '/', ')', '/', ')',
            '(', CHAR_EYE, CHAR_NOSE, CHAR_EYE, ')',
            '|', '_', CHAR_CHEST, '_', '|'
        }
    );

    const Model Bunny::MODEL_IDLE_LEFT
    (
        5,
        {
         '(', 92, '(', 92, ' ',
         '(', CHAR_EYE, CHAR_NOSE, CHAR_EYE, ')',
         '|', '_', CHAR_CHEST, '_', '|'
        }
    );

    //---------------------------------------------------------- Methods

    Bunny::Bunny(int xPos, int yPos) : Collider(xPos, yPos)
    {
        SetState(State::idle);
        ActivateLeftModels(true);
        previousPositionX = GetPosX();
        OnMove.Subscribe([this](weak_ptr<GameObject> _, Direction dir) { OnMoveCallback(dir); });
    }

    void Bunny::Update()
    {
        Collider::Update();

        SwitchWalkIdleState();

        if (state == State::walking && GetPosX() != previousPositionX)
        {
            previousPositionX = GetPosX();
            bool isTimeForLeftModel = Engine::TimeHelper::Instance().IsTimeForFirstOfTwoModels(STEP_ANIM_EVERY_SECONDS);
            ActivateLeftModels(isTimeForLeftModel);
        }

        //prevent movement when game is over
        if (Engine::Simulation::Instance().GetActiveLevel()->IsGameOver() == false)
        {
            HandleVerticalMovement();
            HandleHorizontalMovement();
        }

        UpdateModel();
    }

    void Bunny::ActivateLeftModels(bool activate)
    {
        activeModelJump = activate ? MODEL_JUMP_LEFT : MODEL_JUMP_RIGHT;
        activeModelIdle = activate ? MODEL_IDLE_LEFT : MODEL_IDLE_RIGHT;
        activeModelWalk = activate ? MODEL_WALK_LEFT : MODEL_WALK_RIGHT;
    }

    void Bunny::UpdateModel()
    {
        switch (state)
        {
        case State::defeated:
            SetModel(MODEL_DEFEATED);
            break;

        case State::idle:
            SetModel(activeModelIdle);
            break;

        case State::jumpingUp:
        case State::jumpingDown:
            SetModel(activeModelJump);
            break;

        case State::walking:
            SetModel(activeModelWalk);
            break;
        }
    }

    void Bunny::SwitchWalkIdleState()
    {
        if (Engine::TimeHelper::Instance().GetTime() - lastTimeMovedOnX > 0.2)
        {
            if (state == State::walking)
                SetState(State::idle);
            return;
        }
        else if (state == State::idle)
        {
            SetState(State::walking);
        }
    }

    void  Bunny::HandleVerticalMovement()
    {
        bool isPressingSpace = IsKeyPressed(Key::SPACE);

        if (isPressingSpace == false && IsTouchingGround() && IsJumping())
            SetState(State::walking);


        switch (state)
        {
        case State::idle:
        case State::walking:
            if (isPressingSpace)
            {
                jumpStartingY = GetPosY();
                SetState(State::jumpingUp);
            }
            break;

        case State::jumpingUp:
            if (isPressingSpace)
            {
                TryMove(Direction::up, MOVE_UP_SPEED);
            }
            else
            {
                SetState(State::jumpingDown);
                return;
            }


            if (GetPosY() == jumpStartingY + JUMP_HEIGHT)
                SetState(State::jumpingDown);
            break;
        }
    }

    void Bunny::HandleHorizontalMovement()
    {
        bool isPressingA = IsKeyPressed(Key::A);
        bool isPressingD = IsKeyPressed(Key::D);

        if ((isPressingA && isPressingD) || state == State::defeated)
            return;

        if (isPressingA)
            TryMove(Direction::left, SIDE_MOVEMENT_SPEED);
        if (isPressingD)
            TryMove(Direction::right, SIDE_MOVEMENT_SPEED);
    }

    void Bunny::SetState(State newState)
    {
        if (state == newState)
            return;

        if (state == State::defeated)
            return;

        HandleSounds(state, newState);

        state = newState;
    }

    void Bunny::HandleSounds(State oldState, State newState)
    {
        if (newState == State::jumpingUp)
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/Jump.wav", 0.1);
    }

    double Bunny::GetGravityScale() const
    {
        if (state == State::jumpingUp)
            return 0;

        if (IsKeyPressed(Key::SPACE) && state == State::jumpingDown)
            return MOVE_DOWN_CONTROLLED_SPEED;

        return MOVE_DOWN_SPEED;
    }

    void Bunny::OnMoveCallback(Direction dir)
    {
        if (dir == Direction::right || dir == Direction::left)
            lastTimeMovedOnX = Engine::TimeHelper::Instance().GetTime();
    }

    void Bunny::OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
    {
        if(std::dynamic_pointer_cast<Obstacle>(other))
        {
            SetState(State::defeated);
            OnObstacleHit.Notify();
            return;
        }

        switch (collisionDir)
        {
        case Direction::down:
            SetState(State::idle);
            break;
        case Direction::up:
            if (state == State::jumpingUp)
                SetState(State::jumpingDown);
            break;
        }
    }
}
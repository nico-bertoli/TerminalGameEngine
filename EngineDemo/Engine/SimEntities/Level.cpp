#include "SimEntities/Level.h"

#include "Managers/TimeManager.h"
#include "InputManager/InputManager.h"
#include "Core/Simulation.h"
#include "Managers/AudioManager.h"

namespace Engine
{
    double Level::GetLevelTime() const
    {
        if (IsGameOver())
            return gameOverTime - levelStartedTime;
        else
            return TimeManager::Instance().GetTime() - levelStartedTime;
    }

    void Level::LoadInSimulation()
    {
        isTerminated = false;
        gameOverTime = -1;
        levelStartedTime = TimeManager::Instance().GetTime();
        hasCalledOnPostGameOverDelayEnded = false;

        gameOverWindow.ReadFromFile(GetGameOverWindowPath());
    }

    bool Level::IsPostGameOverPauseEnded() const
    {
        return gameOverTime > 0 && TimeManager::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay();
    }

    bool Level::CanPlayerPressKeyToRestartGame() const
    {
        return TimeManager::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay() + PRESS_ANY_KEY_TO_TERMINATE_GAME_DELAY;
    }

    void Level::OnGameOver()
    {
        if (IsGameOver())
            return;

        gameOverTime = TimeManager::Instance().GetTime();
    }

    void Level::Update()
    {
        if (gameOverTime < 0)
            return;

        if (IsPostGameOverPauseEnded() && hasCalledOnPostGameOverDelayEnded == false)
            OnPostGameOverDelayEnded();
        else if (CanPlayerPressKeyToRestartGame() && InputManager::Instance().IsAnyKeyPressed())
            Terminate();
    }
}
#include "Level.h"

#include "TimeHelper.h"
#include "InputUtils.h"
#include "Simulation.h"
#include "AudioManager.h"

double Level:: GetLevelTime() const
{
    if (IsGameOver())
        return gameOverTime - levelStartedTime;
    else
        return TimeHelper::Instance().GetTime() - levelStartedTime;
}

void Level::LoadInSimulation()
{
    isTerminated = false;
    gameOverTime = -1;
    levelStartedTime = TimeHelper::Instance().GetTime();
    hasCalledOnPostGameOverDelayEnded = false;

    string gameOverWindowCompletePath = "GameOverWindows/" + GetGameOverWindowPath();
    
    gameOverWindow.ReadFromFile
    (
        gameOverWindowCompletePath,
        Simulation::Instance().GetScreenSizeX(),
        Simulation::Instance().GetScreenSizeY()
    );
}

bool Level::IsPostGameOverPauseEnded() const
{
    return gameOverTime > 0 && TimeHelper::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay();
}

bool Level::CanPlayerPressKeyToRestartGame() const
{
    return TimeHelper::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay() + PRESS_ANY_KEY_TO_TERMINATE_GAME_DELAY;
}

void Level::NotifyGameOver()
{
    if (IsGameOver())
        return;

    gameOverTime = TimeHelper::Instance().GetTime();
}

void Level::Update()
{
    if (gameOverTime < 0)
        return;

    if (IsPostGameOverPauseEnded() && hasCalledOnPostGameOverDelayEnded == false)
        OnPostGameOverDelayEnded();
    else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
        Terminate();
}
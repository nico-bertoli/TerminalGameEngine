#pragma once

#include "ISimulationEntity.h"
#include "Terminal.h"
#include "Frame.h"

namespace Engine
{
    class Level : public ISimulationEntity
    {
        friend class Simulation;

        //---------------------------------------------------------- Settings
    private:
        constexpr static double PRESS_ANY_KEY_TO_TERMINATE_GAME_DELAY = 1.5;

        //---------------------------------------------------------- Fields
    private:
        bool hasCalledOnPostGameOverDelayEnded = false;
        double gameOverTime = -1;
        double levelStartedTime = 0;
        bool isTerminated = false;

    protected:
        Engine::Frame gameOverWindow;

        //---------------------------------------------------------- Methods

    public:
        virtual int GetWorldSizeX() const = 0;
        virtual int GetWorldSizeY() const = 0;
        virtual int GetScreenPadding() const = 0;
        virtual int GetMarginsColor() const { return Terminal::BLUE_DARK; }
        virtual const char* GetBackgroundFileName()const { return ""; }
        virtual int GetBackgroundColor() const { return Terminal::BLUE_DARK; }
        double GetLevelTime() const;
        bool IsGameOver() const { return gameOverTime > -1; }
        bool IsTerminated() const { return isTerminated; }

    protected:
        virtual void OnGameOver();
        virtual double ShowGameOverScreenDelay() const = 0;
        void Update() override;
        virtual void OnPostGameOverDelayEnded() { hasCalledOnPostGameOverDelayEnded = true; }
        virtual void LoadInSimulation();
        virtual const char* GetGameOverWindowPath() { return ""; }
        virtual const char* GetPersistenceFilePath() { return ""; }
        virtual void ShowGameOverScreen(int score, int savedBestScore){};

        bool IsPostGameOverPauseEnded() const;
        bool CanPlayerPressKeyToRestartGame() const;
        void Terminate() { isTerminated = true; }

    };
}
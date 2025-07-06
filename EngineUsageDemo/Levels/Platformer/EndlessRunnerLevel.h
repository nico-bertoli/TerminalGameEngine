#pragma once
#include "Config.h"
#include "Level.h"
#include <string>
#include <array>

namespace Platformer
{
    class EndlessRunnerLevel : public Engine::Level
    {
        //---------------------------------------------------------- Settings
    private:
        static const size_t MUSIC_FILES_COUNT = 3;
        static const std::array<const char*, MUSIC_FILES_COUNT> MUSIC_FILES;
        int shownTime = -1;

        //---------------------------------------------------------- Methods
    public:
        int GetWorldSizeX() const override { return 90; }
        int GetWorldSizeY() const override { return 23; }
        int GetScreenPadding() const override { return 4; }
        const char* GetBackgroundFileName()const override { return "Resources/Backgrounds/EndlessRunner.txt"; }

        void LoadInSimulation() override;

    protected:
        void Update()override;
        double ShowGameOverScreenDelay() const override { return 1.5; }
        void OnPostGameOverDelayEnded() override;
        const char* GetPersistenceFilePath() override { return "Resources/Persistence/EndlessRunner.txt"; }
        const char* GetGameOverWindowPath() override { return "Resources/GameOverWindows/EndlessRunner.txt"; }
        void ShowGameOverScreen(int score, int bestScore) override;
        void OnGameOver() override;

    private:
        void PlayRandomMusic();
    };
}
#include "EndlessRunnerLevel.h"
#include "Simulation.h"
#include "StaticCollider.h"
#include "Persistence.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Bunny.h"
#include "ObstaclesSpawner.h"
#include "SimulationPrinter.h"
#include "UIPrinter.h"
#include "Frame.h"
#include "RandomUtils.h"
#include <string>

using std::string;
using std::shared_ptr;
using WindowPosition = Engine::UIPrinter::WindowPosition;

namespace Platformer
{
    const std::array<const char*, EndlessRunnerLevel::MUSIC_FILES_COUNT> EndlessRunnerLevel::MUSIC_FILES =
    {
        "Resources/Music/1.wav",
        "Resources/Music/2.wav",
        "Resources/Music/3.wav"
    };

    void EndlessRunnerLevel::OnPostGameOverDelayEnded()
    {
        Level::OnPostGameOverDelayEnded();
        int score = static_cast<int>(GetLevelTime());

        int savedBestScore = Engine::Persistence::LoadBestScore(GetPersistenceFilePath());
        if (score > savedBestScore)
            Engine::Persistence::SaveBestScore(GetPersistenceFilePath(), score);

        ShowGameOverScreen(score, savedBestScore);
        Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ShowEndScreen.wav");
    }

    void EndlessRunnerLevel::ShowGameOverScreen(int score, int bestScore)
    {
        //setup gameover message
        string messageEnding = score > bestScore ? "new record!" : ("best: " + std::to_string(bestScore));
        string message = "you survived for " + std::to_string(score) + " seconds, " + messageEnding;

        //center message
        string leftSpacing = "";
        for (int i = 0; i < (42 - message.size()) / 2; ++i)
            leftSpacing += " ";
        message = leftSpacing + message;

        gameOverWindow.WriteString(message, '$');

        Engine::Simulation::Instance().GetUIPrinter().PrintWindow(gameOverWindow, Engine::Terminal::WHITE, WindowPosition::CenterX_TopY);
    }

    void EndlessRunnerLevel::OnGameOver()
    {
        if (IsGameOver())
            return;

        Level::OnGameOver();
        Engine::AudioManager::Instance().StopMusic();
        Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/GameOver.wav");
    }

    void EndlessRunnerLevel::LoadInSimulation()
    {
        Level::LoadInSimulation();
        Engine::Simulation& simulation = Engine::Simulation::Instance();

        //----------------- bunny setup
        int bunnyStartingY = static_cast<int>(simulation.GetScreenPadding());
        shared_ptr<Bunny> bunny = std::make_shared<Bunny>(9, bunnyStartingY);
        bunny->OnObstacleHit.Subscribe([this]() { OnGameOver(); });
        simulation.TryAddEntity(bunny);

        //----------------- obstacles spawner setup
        int spawnerPosX = GetWorldSizeX() - GetScreenPadding();

        std::vector<double> minSpawnDelays
        {
            0.9,
            0.4,
            0.28,
            0.25,
            0.22,
            0.22
        };
        std::vector<double> maxSpawnDelays
        {
            1,
            0.6,
            0.43,
            0.4,
            0.32,
            0.22
        };
        std::vector<double> moveSpeeds
        {
            -8,
            -16,
            -32,
            -40,
            -48,
            -48
        };

        double increaseIntensityEverySeconds = 10;
        double stopSpawningWhenPhaseChangesDuration = 1;

        std::vector<int> ySpawnPoints = { 4,8,12 };

        shared_ptr<ObstaclesSpawner> spawner = std::make_shared<ObstaclesSpawner>
        (
            spawnerPosX,
            minSpawnDelays,
            maxSpawnDelays,
            moveSpeeds,
            ySpawnPoints,
            increaseIntensityEverySeconds,
            stopSpawningWhenPhaseChangesDuration
        );

        simulation.TryAddEntity(spawner);
        PlayRandomMusic();
    }

    void EndlessRunnerLevel::PlayRandomMusic()
    {
        const char* randomMusic = MUSIC_FILES[RandomUtils::GetRandomInt(0, static_cast<int>(MUSIC_FILES.size() - 1))];
        Engine::AudioManager::Instance().PlayMusic(randomMusic);
    }

    void EndlessRunnerLevel::Update()
    {
        Level::Update();
        double runTime = Engine::Simulation::Instance().GetActiveLevel()->GetLevelTime();
        int newTime = static_cast<int>(runTime);
        if (shownTime != newTime)
        {
            string header = "TIME: " + std::to_string(newTime);
            Engine::Simulation::Instance().GetUIPrinter().PrintOnHeader(header, 0, Engine::Terminal::WHITE);
            shownTime = newTime;
        }
    }

}


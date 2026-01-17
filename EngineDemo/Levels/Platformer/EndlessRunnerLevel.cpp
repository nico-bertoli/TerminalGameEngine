#include "EndlessRunnerLevel.h"
#include "Core/Simulation.h"
#include "SimEntities/StaticCollider.h"
#include "Managers/PersistenceManager.h"
#include "InputManager/InputManager.h"
#include "Managers/AudioManager.h"
#include "Bunny.h"
#include "ObstaclesSpawner.h"
#include "Printers/SimulationPrinter.h"
#include "Printers/UIPrinter.h"
#include "Core/Frame.h"
#include "Utils/RandomUtils.h"
#include <string>

using std::string;
using std::shared_ptr;
using WindowPosition = Engine::UIPrinter::WindowPosition;

namespace Platformer
{
    void EndlessRunnerLevel::OnPostGameOverDelayEnded()
    {
        Level::OnPostGameOverDelayEnded();
        int score = static_cast<int>(GetLevelTime());

        int saved_best_score = Engine::PersistenceManager::LoadBestScore(GetPersistenceFilePath());
        if (score > saved_best_score)
            Engine::PersistenceManager::SaveBestScore(GetPersistenceFilePath(), score);

        ShowGameOverScreen(score, saved_best_score);
        Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ShowEndScreen.wav");
    }

    void EndlessRunnerLevel::ShowGameOverScreen(int score, int best_score)
    {
        //setup gameover message
        string message_ending = score > best_score ? "new record!" : ("best: " + std::to_string(best_score));
        string message = "you survived for " + std::to_string(score) + " seconds, " + message_ending;

        //center message
        string left_spacing = "";
        for (int i = 0; i < (42 - message.size()) / 2; ++i)
            left_spacing += " ";
        message = left_spacing + message;

        game_over_window_.WriteString(message, '$');

        Engine::Simulation::Instance().GetUIPrinter().PrintWindow(game_over_window_, Engine::color::kWhite, WindowPosition::kCenterXTopY);
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
        bunny->on_obstacle_hit.Subscribe([this]() { OnGameOver(); });
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
        const char* randomMusic = kMusicFiles[RandomUtils::GetRandomInt(0, static_cast<int>(kMusicFiles.size() - 1))];
        Engine::AudioManager::Instance().PlayMusic(randomMusic);
    }

    void EndlessRunnerLevel::Update()
    {
        Level::Update();
        double run_time = Engine::Simulation::Instance().GetActiveLevel()->GetLevelTime();
        int new_time = static_cast<int>(run_time);
        if (shown_time_ != new_time)
        {
            string header = "TIME: " + std::to_string(new_time);
            Engine::Simulation::Instance().GetUIPrinter().PrintOnHeader(header, 0, Engine::color::kWhite);
            shown_time_ = new_time;
        }
    }

}


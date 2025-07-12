#pragma once
#include "Level.h"

namespace SpaceInvaders
{
    class Alien;
    class AliensController;

    class SpaceInvadersLevel : public Engine::Level
    {
        //------------------------------------------------------------------- Aliens Position Settings
    public:
        static const size_t ALIEN_WIDTH = 4;
        static const size_t ALIEN_HEIGHT = 2;

        static const size_t ALIENS_COUNT_Y = 5;
        static const size_t ALIENS_COUNT_X = 11;
        static const size_t SPACE_BETWEEN_ALIENS_X = 2;
        static const size_t SPACE_BETWEEN_ALIENS_Y = 1;

        static const size_t ALIENS_SPACE_FROM_MARGINS_X = 5;
        static const size_t ALIENS_SPACE_FROM_TOP_MARGIN = 3;

        //------------------------------------------------------------------- Aliens Position Settings
        static const size_t SHIELD_SIZE_X = 7;
        static const size_t SHIELD_SIZE_Y = 3;

        //------------------------------------------------------------------- Other Settings
        static const size_t GAME_OVER_Y = 8;
        static constexpr double LOAD_WAVE_TIME = 2;

        //------------------------------------------------------------------- Fields
    private:
        size_t waveNumber;
        int score;
        bool isLoadingWave;
        double startedLoadingWaveTime;
        std::shared_ptr<AliensController> aliensController;

        //------------------------------------------------------------------- Methods
    public:
        int GetWorldSizeX() const override;
        int GetWorldSizeY() const override { return 50; }
        int GetScreenPadding() const override { return 6; }
        void LoadInSimulation() override;
        size_t GetWaveNumber() { return waveNumber; }
        void IncreasePlayerScore(size_t increment);
        bool IsLoadingWave() { return isLoadingWave; }

    protected:
        void Update()override;
        double ShowGameOverScreenDelay() const override { return 0.2; }
        const char* GetPersistenceFilePath() override { return "Resources/Persistence/SpaceInvaders.txt"; }
        const char* GetGameOverWindowPath() override { return "Resources/GameOverWindows/SpaceInvaders.txt"; }
        void OnPostGameOverDelayEnded() override;
        void ShowGameOverScreen(int score, int savedBestScore) override;
        void OnGameOver() override;

    private:
        void LoadAliens();
        void LoadPlayerTank();
        void LoadShield(int xPos, int yPos);
        void LoadShields(int yPos, size_t count, std::vector<size_t> spacing);
        void InitHeader();
        void PrintScore();
        void PrintHealth(size_t health);
        void PrintWave();
        const type_info& GetAlienTypeForRow(int rowIndex);
        void AddAliensRowToSimulation(int yPos, int rowIndex);
        std::shared_ptr<Alien> CreateAlienOfType(const type_info& alienType, int xPos, int yPos, int xIndex, int yIndex);
        void OnWaveCompleted();
        void LoadNewWave();
        void OnPlayerTakesDamage(size_t remainingHealth);
    };
}
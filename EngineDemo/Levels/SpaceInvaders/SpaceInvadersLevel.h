#pragma once
#include "SimEntities/Level.h"
#include <typeinfo>

namespace SpaceInvaders
{
    class Alien;
    class AliensController;

    class SpaceInvadersLevel : public Engine::Level
    {
        //------------------------------------------------------------------- Aliens Position Settings
    public:
        static constexpr size_t kAlienWidth = 4;
        static constexpr size_t kAlienHeight = 2;

        static constexpr size_t kAliensCountY = 5;
        static constexpr size_t kAliensCountX = 11;
        static constexpr size_t kSpaceBetweenAliensX = 2;
        static constexpr size_t kSpaceBetweenAliensY = 1;

        static constexpr size_t kAliensSpaceFromMarginsX = 5;
        static constexpr size_t kAliensSpaceFromTopMargin = 3;

        //------------------------------------------------------------------- Aliens Position Settings
        static constexpr size_t kShieldSizeX = 7;
        static constexpr size_t kShieldSizeY = 3;

        //------------------------------------------------------------------- Other Settings
        static constexpr size_t kGameOverY = 8;
        static constexpr double kLoadWaveTime = 2;

        //------------------------------------------------------------------- Fields
    private:
        size_t wave_number_;
        int score_;
        bool is_loading_wave_;
        double started_loading_wave_time_;
        std::shared_ptr<AliensController> aliens_controller_;

        //------------------------------------------------------------------- Methods
    public:
        int GetWorldSizeX() const override;
        int GetWorldSizeY() const override { return 50; }
        int GetScreenPadding() const override { return 6; }
        void LoadInSimulation() override;
        size_t GetWaveNumber() { return wave_number_; }
        void IncreasePlayerScore(size_t increment);
        bool IsLoadingWave() { return is_loading_wave_; }

    protected:
        void Update()override;
        double ShowGameOverScreenDelay() const override { return 0.2; }
        const char* GetPersistenceFilePath() override { return "Resources/Persistence/SpaceInvaders.txt"; }
        const char* GetGameOverWindowPath() override { return "Resources/GameOverWindows/SpaceInvaders.txt"; }
        void OnPostGameOverDelayEnded() override;
        void ShowGameOverScreen(int score, int saved_best_score) override;
        void OnGameOver() override;

    private:
        void LoadAliens();
        void LoadPlayerTank();
        void LoadShield(int x_pos, int y_pos);
        void LoadShields(int y_pos, size_t count, std::vector<size_t> spacing);
        void InitHeader();
        void PrintScore();
        void PrintHealth(size_t health);
        void PrintWave();
        const std::type_info& GetAlienTypeForRow(int row_index);
        void AddAliensRowToSimulation(int y_pos, int row_index);
        std::shared_ptr<Alien> CreateAlienOfType(const std::type_info& alien_type, int x_pos, int y_pos, int x_index, int y_index);
        void OnWaveCompleted();
        void LoadNewWave();
        void OnPlayerTakesDamage(size_t remaining_health);
    };
}
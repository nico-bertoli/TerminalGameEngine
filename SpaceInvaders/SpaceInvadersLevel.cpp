#include "SpaceInvadersLevel.h"
#include "Simulation.h"
#include "AlienLowScore.h"
#include "AlienMidScore.h"
#include "AlienHighScore.h"
#include "PlayerTank.h"
#include "AliensController.h"
#include "AudioManager.h"
#include "Persistence.h"
#include "UIPrinter.h"
#include "Printer.h"
#include "ShieldPart.h"
#include "UfoSpawner.h"

#include <string>

using WindowPosition = Engine::UIPrinter::WindowPosition;
using Engine::Simulation;
using Engine::Direction;
using std::string;
using std::shared_ptr;
using std::vector;

namespace SpaceInvaders
{


	int SpaceInvadersLevel::GetWorldSizeX() const
	{
		return
			ALIENS_COUNT_X * ALIEN_WIDTH
			+
			(ALIENS_COUNT_X - 1) * SPACE_BETWEEN_ALIENS_X
			+
			2 * ALIENS_SPACE_FROM_MARGINS_X
			+
			2 * GetScreenPadding();
	}

	void SpaceInvadersLevel::LoadInSimulation()
	{
		Level::LoadInSimulation();

		waveNumber = 1;
		score = 0;
		isLoadingWave = false;
		double startedLoadingWaveTime = -1;

		aliensController = std::make_shared<AliensController>(std::dynamic_pointer_cast<SpaceInvadersLevel>(shared_from_this()));
		aliensController->OnWaveCompleted.Subscribe([this]() { OnWaveCompleted(); });
		aliensController->OnGroundTouched.Subscribe([this]() { OnGameOver(); });
		Simulation::Instance().TryAddEntity(aliensController);

		LoadAliens();
		LoadPlayerTank();
		InitHeader();

		shared_ptr<UfoSpawner> ufoSpawner = std::make_shared<UfoSpawner>(GetWorldSizeX() - 5, GetWorldSizeY() - GetScreenPadding() - 2, Direction::left);
		Simulation::Instance().TryAddEntity(ufoSpawner);

#if !CHEAT_SPACEINV_DISABLE_SHIELDS
		vector<size_t> shieldsSpacing = { 9,9,10,9,9 };
		LoadShields(9, 4, shieldsSpacing);
#endif
	}

	void SpaceInvadersLevel::OnGameOver()
	{
		if (IsGameOver())
			return;

		Level::OnGameOver();
		Engine::AudioManager::Instance().StopMusic();
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/gameOver.wav");
	}

	void SpaceInvadersLevel::Update()
	{
		Level::Update();
		LoadNewWave();
	}

	void SpaceInvadersLevel::OnPostGameOverDelayEnded()
	{
		Level::OnPostGameOverDelayEnded();

		int savedBestScore = Engine::Persistence::LoadBestScore(GetPersistenceFilePath());
		if (score > savedBestScore)
			Engine::Persistence::SaveBestScore(GetPersistenceFilePath(), score);

		ShowGameOverScreen(score, savedBestScore);
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/ShowEndScreen.wav");
	}

	void SpaceInvadersLevel::ShowGameOverScreen(int score, int bestScore)
	{
		string messageEnding = score > bestScore ? ", new record!" : (", best: " + std::to_string(bestScore));
		string message = "score: " + std::to_string(score) + messageEnding;

		//center message
		string leftSpacing = "";
		for (int i = 0; i < (42 - message.size()) / 2; ++i)
			leftSpacing += " ";
		message = leftSpacing + message;

		gameOverWindow.WriteString(message, '$');

		Simulation::Instance().GetUIPrinter().PrintWindow(gameOverWindow, Engine::Terminal::WHITE, WindowPosition::CenterX_CenterY);
	}

	void SpaceInvadersLevel::IncreasePlayerScore(size_t increment)
	{
		score += static_cast<int>(increment);
		PrintScore();
	}

	void SpaceInvadersLevel::InitHeader()
	{
		PrintScore();
		PrintWave();
	}

	void SpaceInvadersLevel::PrintScore()
	{
		string scoreString = "score: " + std::to_string(score);
		int xPos = static_cast<int>(Simulation::Instance().GetScreenSizeX() / 2 - scoreString.size() / 2);
		Simulation::Instance().GetUIPrinter().PrintOnHeader(scoreString, xPos, Engine::Terminal::WHITE);
	}

	void SpaceInvadersLevel::PrintHealth(size_t health)
	{
		int xPos = Engine::Printer::LEFT_MARGIN_SIZE;

		string healthStr = "";
		for (int i = 1; i <= PlayerTank::MAX_HEALTH; i++)
			healthStr += i <= health ? "<3 " : "  ";

		Simulation::Instance().GetUIPrinter().PrintOnHeader(healthStr, xPos, Engine::Terminal::RED);
	}

	void SpaceInvadersLevel::PrintWave()
	{
		Engine::UIPrinter uiPrinter = Simulation::Instance().GetUIPrinter();
		string waveStr = "wave: " + std::to_string(waveNumber);

		int waveStringPosX = static_cast<int>(uiPrinter.GetMaxTerminalX() - waveStr.length());
		Simulation::Instance().GetUIPrinter().PrintOnHeader(waveStr, waveStringPosX, Engine::Terminal::WHITE);
	}


	void SpaceInvadersLevel::LoadPlayerTank()
	{
		int xPos = GetWorldSizeX() / 2;
		int yPos = GetScreenPadding();
		shared_ptr<PlayerTank> playerTank = std::make_shared<PlayerTank>(xPos, yPos, this);
		playerTank->OnDamageTaken.Subscribe([this](size_t health) { OnPlayerTakesDamage(health); });
		PrintHealth(playerTank->GetHealth());
		Simulation::Instance().TryAddEntity(playerTank);
	}

	void SpaceInvadersLevel::OnPlayerTakesDamage(size_t remainingHealth)
	{
		PrintHealth(remainingHealth);
		if (remainingHealth == 0)
			OnGameOver();
	}

	void SpaceInvadersLevel::LoadAliens()
	{
		aliensController->Reset(ALIENS_COUNT_X, ALIENS_COUNT_Y);
		int yPos = GetWorldSizeY() - GetScreenPadding() - ALIENS_SPACE_FROM_TOP_MARGIN - ALIEN_HEIGHT;
		int yIndex = 0;
		while (yIndex < ALIENS_COUNT_Y)
		{
			AddAliensRowToSimulation(yPos, yIndex);
			yPos -= (ALIEN_HEIGHT + SPACE_BETWEEN_ALIENS_Y);
			++yIndex;
		}
	}

	const type_info& SpaceInvadersLevel::GetAlienTypeForRow(int yIndex)
	{
		if (yIndex == 0)
			return typeid(AlienHighScore);
		else if (yIndex < 3)
			return typeid(AlienMidScore);
		else
			return typeid(AlienLowScore);
	}

	void SpaceInvadersLevel::AddAliensRowToSimulation(int yPos, int yIndex)
	{
		int xPos = GetScreenPadding() + ALIENS_SPACE_FROM_MARGINS_X;
		const type_info& alienType = GetAlienTypeForRow(yIndex);
		int xIndex = 0;
		while (xIndex < ALIENS_COUNT_X)
		{
			shared_ptr<Alien> alien = CreateAlienOfType(alienType, xPos, yPos, xIndex, yIndex);

			Simulation::Instance().TryAddEntity(alien);
			aliensController->RegisterAlien(alien, xIndex, yIndex);

			++xIndex;
			xPos += ALIEN_WIDTH + SPACE_BETWEEN_ALIENS_X;
		}
	}

	shared_ptr<Alien> SpaceInvadersLevel::CreateAlienOfType(const type_info& alienType, int xPos, int yPos, int xIndex, int yIndex)
	{
		if (alienType == typeid(AlienHighScore))
			return std::make_shared<AlienHighScore>(xPos, yPos, xIndex, yIndex);
		else if (alienType == typeid(AlienMidScore))
			return std::make_shared<AlienMidScore>(xPos, yPos, xIndex, yIndex);
		else if (alienType == typeid(AlienLowScore))
			return std::make_shared<AlienLowScore>(xPos, yPos, xIndex, yIndex);
		else
			throw std::invalid_argument("invalid alien type receiveds");
	}

	void SpaceInvadersLevel::LoadShields(int yPos, size_t count, vector<size_t> spacing)
	{
		for (int i = 0; i < count; ++i)
		{
			size_t shieldSpacing = 0;
			for (int j = 0; j <= i; ++j)
				shieldSpacing += spacing[j];

			int x = static_cast<int>(GetScreenPadding() + shieldSpacing + SHIELD_SIZE_X * i);
			LoadShield(x, yPos);
		}
	}

	void SpaceInvadersLevel::LoadShield(int xPos, int yPos)
	{
		for (int y = 0; y < SHIELD_SIZE_Y; ++y)
		{
			for (int x = 0; x < SHIELD_SIZE_X; ++x)
			{
				// bottom hole
				if (y == 0 && x > 1 && x < SHIELD_SIZE_X - 2)
					continue;
				//smooth angles
				if (y == SHIELD_SIZE_Y - 1 && (x == 0 || x == SHIELD_SIZE_X - 1))
					continue;

				shared_ptr<ShieldPart> shieldPart = std::make_shared<ShieldPart>(xPos + x, yPos + y);
				Simulation::Instance().TryAddEntity(shieldPart);
			}
		}
	}

	void SpaceInvadersLevel::OnWaveCompleted()
	{
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/WaveComplete.wav");
		isLoadingWave = true;
		waveNumber++;
		PrintWave();
		startedLoadingWaveTime = Engine::TimeHelper::Instance().GetTime();
	}

	void SpaceInvadersLevel::LoadNewWave()
	{
		if (isLoadingWave && Engine::TimeHelper::Instance().GetTime() - startedLoadingWaveTime > LOAD_WAVE_TIME)
		{
			LoadAliens();
			isLoadingWave = false;
		}
	}
}
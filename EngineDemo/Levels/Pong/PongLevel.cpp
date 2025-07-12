#include "PongLevel.h"
#include "Simulation.h"
#include "PongBar.h"
#include "PongBall.h"
#include "AudioManager.h"
#include "UIPrinter.h"

namespace Pong
{
	size_t PongLevel::scorePlayer1 = 0;
	size_t PongLevel::scorePlayer2 = 0;

	void PongLevel::LoadInSimulation()
	{
		Level::LoadInSimulation();
		Engine::Simulation& simulation = Engine::Simulation::Instance();

		//--------------- bars general settings
		char barsChar = -37;
		int startingPosX = GetWorldSizeX() / 2 - 1;
		int barsSize = 8;
		double barsMoveSpeed = 32;
		double deflectFactor = 2.5;

		//--------------- bottom bar

		auto bottomBar = std::make_shared<PongBar>
		(
			startingPosX,
			GetScreenPadding(),
			barsSize,
			1,
			barsChar,
			barsMoveSpeed,
			deflectFactor,
			true
		);
		simulation.TryAddEntity(bottomBar);

		//--------------- top bar
		auto topBar = std::make_shared<PongBar>
		(
			startingPosX,
			GetWorldSizeY() - GetScreenPadding() - 1,
			barsSize,
			1,
			barsChar,
			barsMoveSpeed,
			deflectFactor,
			false
		);
		simulation.TryAddEntity(topBar);

		//--------------- ball
		double ballSpeed = 16;
		auto pongBall = std::make_shared<PongBall>(this, GetWorldSizeX() / 2, GetWorldSizeY() / 2, ballSpeed);
		pongBall->OnGoal.Subscribe([this]() { OnGameOver(); });
		simulation.TryAddEntity(pongBall);
		RefreshHeader();
	}

	void PongLevel::IncreaseP1Score()
	{
		++scorePlayer1;
		RefreshHeader();
	}

	void PongLevel::IncreaseP2Score()
	{
		++scorePlayer2;
		RefreshHeader();
	}

	void PongLevel::RefreshHeader()
	{
		Engine::Simulation::Instance().GetUIPrinter().
			PrintOnHeader(std::to_string(scorePlayer1) + " - " + std::to_string(scorePlayer2), 0, Engine::Terminal::WHITE);
	}

	void PongLevel::OnPostGameOverDelayEnded()
	{
		Level::OnPostGameOverDelayEnded();
		Terminate();
	}

	void PongLevel::OnGameOver()
	{
		Level::OnGameOver();
		Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Pong/Goal.wav");
	}
}
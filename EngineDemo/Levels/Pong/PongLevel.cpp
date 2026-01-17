#include "PongLevel.h"
#include "Core/Simulation.h"
#include "PongBar.h"
#include "PongBall.h"
#include "Managers/AudioManager.h"
#include "Printers/UIPrinter.h"

namespace Pong
{
	size_t PongLevel::score_player_1_ = 0;
	size_t PongLevel::score_player_2_ = 0;

	void PongLevel::LoadInSimulation()
	{
		Level::LoadInSimulation();
		Engine::Simulation& simulation = Engine::Simulation::Instance();

		//--------------- bars general settings
		char bars_char = '#';
		int starting_pos_x = GetWorldSizeX() / 2 - 1;
		int bars_size = 8;
		double bars_move_speed = 32;
		double deflect_factor = 2.5;

		//--------------- bottom bar

		auto bottom_bar = std::make_shared<PongBar>
		(
			starting_pos_x,
			GetScreenPadding(),
			bars_size,
			1,
			bars_char,
			bars_move_speed,
			deflect_factor,
			true
		);
		simulation.TryAddEntity(bottom_bar);

		//--------------- top bar
		auto top_bar = std::make_shared<PongBar>
		(
			starting_pos_x,
			GetWorldSizeY() - GetScreenPadding() - 1,
			bars_size,
			1,
			bars_char,
			bars_move_speed,
			deflect_factor,
			false
		);
		simulation.TryAddEntity(top_bar);

		//--------------- ball
		double ball_speed = 16;
		auto pong_ball = std::make_shared<PongBall>(this, GetWorldSizeX() / 2, GetWorldSizeY() / 2, ball_speed);
		pong_ball->on_goal.Subscribe([this]() { OnGameOver(); });
		simulation.TryAddEntity(pong_ball);
		RefreshHeader();
	}

	void PongLevel::IncreaseP1Score()
	{
		++score_player_1_;
		RefreshHeader();
	}

	void PongLevel::IncreaseP2Score()
	{
		++score_player_2_;
		RefreshHeader();
	}

	void PongLevel::RefreshHeader()
	{
		Engine::Simulation::Instance().GetUIPrinter().
			PrintOnHeader(std::to_string(score_player_1_) + " - " + std::to_string(score_player_2_), 0, Engine::color::kWhite);
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
#include "Config.h"
#include "AliensController.h"
#include "Alien.h"
#include "SimEntities/Level.h"
#include "Managers/TimeManager.h"
#include "SpaceInvadersLevel.h"
#include "Managers/DebugManager.h"
#include "Utils/RandomUtils.h"
#include "SimEntities/GameObject.h"
#include <cassert>

using std::string;
using std::shared_ptr;
using std::weak_ptr;
using Engine::Collider;
using Engine::Direction;
using Engine::GameObject;

namespace SpaceInvaders
{
	

	double AliensController::GetSpeedX() const
	{
		return kBaseMoveSpeed +
			GetEliminatedAliensMultiplier() * kAllAliensEliminatedMoveSpeedIncrement +
			GetWaveMultiplier() * kWaveNumberSpeedIncreaseFactor;
	}

	double AliensController::GetNextShotDelay()const
	{
		double delay = kBaseShootDelay -
			GetEliminatedAliensMultiplier() * kAllAliensEliminatedShootDelayReduction -
			GetWaveMultiplier() * kWaveNumberShotDelayReductionFactor +
			RandomUtils::GetRandomDouble(-kShotsRandomness / 2, kShotsRandomness / 2);

		return delay > kMinShowDelay ? delay : kMinShowDelay;
	}

	double AliensController::GetEliminatedAliensMultiplier()const
	{
		return static_cast<double>(GetDestroyedAliensCount()) / (GetStartingAliensCount() - 1);
	}

	double AliensController::GetWaveMultiplier()const
	{
		return static_cast<double>((level->GetWaveNumber() - 1));
	}

	void AliensController::Reset(int aliens_count_x, int aliens_count_y)
	{
		aliens_count_ = aliens_count_x * aliens_count_y;
		aliensGrid.Resize(aliens_count_x, aliens_count_y);
		frontLine.Init(aliens_count_x);
	}

	void AliensController::Update()
	{
#if DEBUG_MODE
		string totBoost = "tot boost: " + std::to_string(GetSpeedX());
		string eliminationsBoost = " elim. multiplier:" + std::to_string(GetEliminatedAliensMultiplier());
		string waveBoost = " wave multiplier:" + std::to_string(GetWaveMultiplier());
		string debugStr = totBoost + " | " + eliminationsBoost + " | " + waveBoost;
		Engine::DebugManager::Instance().PrintGenericLog(debugStr, 0);
#endif

		HandleMovement();
		HandleShooting();
	}

	void AliensController::RegisterAlien(shared_ptr<Alien> alien, int x_pos, int y_pos)
	{
		assert(alien != nullptr);
		assert(y_pos < GetAliensGridHeight());
		assert(x_pos < GetAliensGridWidth());

		aliensGrid.Get(x_pos, y_pos) = alien;

		if (y_pos == GetAliensGridHeight() - 1)
			frontLine.Set(x_pos, alien);

		alien->on_move.Subscribe
		(
			[this](weak_ptr<GameObject> alien, Direction dir) { OnAlienMovedCallback(alien, dir); }
		);

		alien->on_destroy_event.Subscribe
		(
			[this](weak_ptr<Collider> alien_obj) { OnAlienDestroyedCallback(alien_obj); }
		);
	}

	void AliensController::OnAlienMovedCallback(weak_ptr<GameObject> alien_weak, Direction move_direction)
	{
		shared_ptr<GameObject> alien = alien_weak.lock();
		if (move_direction == x_move_direction_ && alien != nullptr)
		{
			int alien_x_pos = alien->GetPosX();
			if (
				alien_x_pos == level->GetScreenPadding() ||
				alien_x_pos == level->GetWorldSizeX() - level->GetScreenPadding() - alien->GetModelWidth()
				)
				OnAliensReachMargin();
		}
	}

	void AliensController::MoveAliens(Direction dir, double speed)
	{
		for (int y = 0; y < GetAliensGridHeight(); ++y)
			for (int x = 0; x < GetAliensGridWidth(); ++x)
			{
				shared_ptr<Alien> alien = aliensGrid.Get(x, y).lock();
				if (alien)
					alien->TryMove(dir, speed);
			}
				
	}

	void AliensController::OnAliensReachMargin()
	{
		x_move_direction_ = DirectionUtils::GetInverseDirection(x_move_direction_);
		is_time_to_move_aliens_down_ = true;
	}

	static int calledTimes = 0;

	void AliensController::OnAlienDestroyedCallback(weak_ptr<GameObject> alien_obj_weak)
	{
		shared_ptr<GameObject> alien_obj = alien_obj_weak.lock();
		if (alien_obj != nullptr)
		{
			shared_ptr<Alien> alien = std::dynamic_pointer_cast<Alien>(alien_obj);
			frontLine.ReplaceDestroyedElement(alien, aliensGrid);

			--aliens_count_;
			if (aliens_count_ == 0)
				on_wave_completed.Notify();
		}
	}

	void AliensController::HandleShooting()
	{
		if (Engine::TimeManager::Instance().GetTime() - last_shot_time_ > shot_delay_)
		{
			shared_ptr<Alien> front_line_alien = frontLine.GetRandom();
			if (front_line_alien == nullptr)
				return;
			front_line_alien->Shot();
			last_shot_time_ = Engine::TimeManager::Instance().GetTime();
			shot_delay_ = GetNextShotDelay();
		}
	}

	void AliensController::HandleMovement()
	{
		if (is_time_to_move_aliens_down_)
		{
			if (frontLine.GetMinY() - 1 <= SpaceInvadersLevel::kGameOverY)
				on_ground_touched.Notify();

			MoveAliens(Direction::kDown, 9999);
			is_time_to_move_aliens_down_ = false;
		}
		else
			MoveAliens(x_move_direction_, GetSpeedX());
	}
}
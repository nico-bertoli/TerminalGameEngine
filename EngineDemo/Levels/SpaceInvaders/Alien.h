#pragma once
#include "Enemy.h"
#include "General/Vector2Int.h"
#include <nbase_kit/event.h>

namespace SpaceInvaders
{
	class Alien : public Enemy
	{
		friend class AliensController;

		//------------------------------------------------------ Settings
	private:
		static constexpr size_t kProjectileSpeed = 8;

		//------------------------------------------------------ Fields
	public:
		nbase_kit::Event<std::weak_ptr<Collider>> on_destroy_event;

	protected:
		const Engine::Model* animation_model_1_;
		const Engine::Model* animation_model_2_;
		bool is_first_animation_frame_time_ = false;

	private:
		size_t grid_index_x_;
		size_t grid_index_y_;

		//------------------------------------------------------ Methods
	public:
		Alien(int x_pos, int y_pos, size_t x_index_in_formation, size_t y_index_in_formation) :
			Enemy(x_pos, y_pos), grid_index_x_(x_index_in_formation), grid_index_y_(y_index_in_formation)
		{
		}

		bool CanExitScreenSpace() const override { return false; }
		size_t GetIndexInGridX() { return grid_index_x_; }
		size_t GetIndexInGridY() { return grid_index_y_; }

		void Shot();

	protected:
		void OnDestroy() override;
		void Update() override;
		void StepAnimation() { SetModel(is_first_animation_frame_time_ ? *animation_model_1_ : *animation_model_2_); }
	};
}
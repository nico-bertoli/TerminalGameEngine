#pragma once
#include "Projectile.h"

namespace SpaceInvaders
{
	class PlayerProjectile : public Projectile
	{
		//---------------------------------------------------------- Fields
	private:
		static inline const Engine::Model kModel = Engine::Model(1, { '|' });

		//---------------------------------------------------------- Methodss
	public:
		using Projectile::Projectile;

	protected:
		Engine::TerminalColor GetColor() const override { return Engine::color::kGreen; }
		void InitModel() override { SetModel(kModel); }
		void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collision_dir) override;
	};
}
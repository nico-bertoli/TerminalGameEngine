#pragma once
#include "Projectile.h"

namespace SpaceInvaders
{
	class PlayerProjectile : public Projectile
	{
		//---------------------------------------------------------- Fields
	private:
		static const Engine::Model MODEL;

		//---------------------------------------------------------- Methodss
	public:
		using Projectile::Projectile;

	protected:
		Engine::TerminalColor GetColor() const override { return Engine::TerminalColor::GREEN; }
		void InitModel() override { SetModel(MODEL); }
		void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
	};
}
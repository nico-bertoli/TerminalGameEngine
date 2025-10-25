#pragma once
#include "Projectile.h"
#include "SimEntities/GameObject.h"

namespace SpaceInvaders
{
	class EnemyProjectile : public Projectile
	{
		//---------------------------------------------------------- Fields
	private:
		static const Engine::Model MODEL;

		//---------------------------------------------------------- Methodss
	public:
		using Projectile::Projectile;

	protected:
		Engine::TerminalColor GetColor() const override { return Engine::TerminalColor::RED; }
		void InitModel() override { SetModel(MODEL); }
		void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
	};
}
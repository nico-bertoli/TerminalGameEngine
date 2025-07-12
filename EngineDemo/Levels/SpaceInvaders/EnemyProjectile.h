#pragma once
#include "Projectile.h"
#include "GameObject.h"

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
		int GetColor() const override { return Engine::Terminal::RED; }
		void InitModel() override { SetModel(MODEL); }
		void OnCollisionEnter(std::shared_ptr<Collider> other, Engine::Direction collisionDir) override;
	};
}
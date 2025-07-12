#pragma once
#include "Collider.h"

namespace SpaceInvaders
{
	class Enemy : public Engine::Collider
	{
		//------------------------------------------------------ Fields
	public:
		using Collider::Collider;
	protected:
		bool isFirsAnimationFrameTime;

		//------------------------------------------------------ Methods
	public:
		virtual size_t GetScore() const = 0;

	protected:
		double GetGravityScale() const override { return 0; }
		void OnDestroy() override;
		virtual int GetDestroyedParticlesColor() { return Engine::Terminal::GREEN; }
	};
}
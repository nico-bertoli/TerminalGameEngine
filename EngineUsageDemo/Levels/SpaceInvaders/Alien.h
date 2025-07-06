#pragma once
#include "Enemy.h"
#include "Event.h"

namespace SpaceInvaders
{
	class Alien : public Enemy
	{
		friend class AliensController;

		//------------------------------------------------------ Settings
	private:
		static const size_t PROJECTILE_SPEED = 8;

		//------------------------------------------------------ Fields
	public:
		Event<std::weak_ptr<Collider>> OnDestroyEvent;

	protected:
		const Engine::Model* animationModel1;
		const Engine::Model* animationModel2;

	private:
		size_t gridIndexX;
		size_t gridIndexY;

		//------------------------------------------------------ Methods
	public:
		Alien(int xPos, int yPos, size_t xIndexInFormation, size_t yIndexInFormation) :
			Enemy(xPos, yPos), gridIndexX(xIndexInFormation), gridIndexY(yIndexInFormation)
		{
		}

		bool CanExitScreenSpace() const override { return false; }
		size_t GetIndexInGridX() { return gridIndexX; }
		size_t GetIndexInGridY() { return gridIndexY; }

		void Shot();

	protected:
		void OnDestroy() override;
		void Update() override;
		void StepAnimation() { SetModel(isFirsAnimationFrameTime ? *animationModel1 : *animationModel2); }
	};
}
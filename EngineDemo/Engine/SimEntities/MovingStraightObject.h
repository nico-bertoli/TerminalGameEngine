#pragma once
#include "SimEntities/Collider.h"
#include <iostream>
#include <stdlib.h>
#include <cassert>

namespace Engine
{
	class MovingStraightObject : public Collider
	{
		//---------------------------------------------------------- Fields
	private:
		Direction moveDirection;
		const double moveSpeed;

		//---------------------------------------------------------- Methods
	public:
		MovingStraightObject(int xPos, int yPos, Direction moveDir, double moveSpeed);

	protected:
		void Update() override;
	};
}
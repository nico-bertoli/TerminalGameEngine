#pragma once
#include "GameObject.h"
#include <unordered_set>
#include <array>
#include <memory>	

namespace Engine
{
	class Collider : public GameObject
	{
		friend class Simulation;

		//---------------------------------------------------------- Fields

	protected:
		std::array<std::list<std::weak_ptr<Collider>>, 4> collisions;

		//---------------------------------------------------------- Methods
	public:
		using GameObject::GameObject;

	protected:

		virtual void OnCollisionEnter(std::shared_ptr<Collider> other, Direction collisionDir) {}
		virtual void OnCollisionExit(Direction endingCollisionDir) {}

	private:
		void CALLED_BY_SIM_NotifyCollisionEnter(std::unordered_set<std::shared_ptr<Collider>>collidingObjects, Direction collisionDir);
		void CALLED_BY_SIM_NotifyCollisionEnter(std::shared_ptr<Collider> collidingObject, Direction collisionDir);
		void CALLED_BY_SIM_UpdateEndedCollisions(const std::array<std::unordered_set<std::shared_ptr<Collider>>, 4>& newCollisions);
	};
}
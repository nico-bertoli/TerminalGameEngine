#pragma once
#include "SimEntities/GameObject.h"
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
		std::array<std::list<std::weak_ptr<Collider>>, 4> collisions_;

		//---------------------------------------------------------- Methods
	public:
		using GameObject::GameObject;

	protected:

		virtual void OnCollisionEnter(std::shared_ptr<Collider> other, Direction collision_dir) {}
		virtual void OnCollisionExit(Direction ending_collision_dir) {}

	private:
		void CALLED_BY_SIM_NotifyCollisionEnter(std::unordered_set<std::shared_ptr<Collider>>colliding_objects, Direction collision_dir);
		void CALLED_BY_SIM_NotifyCollisionEnter(std::shared_ptr<Collider> colliding_object, Direction collision_dir);
		void CALLED_BY_SIM_UpdateEndedCollisions(const std::array<std::unordered_set<std::shared_ptr<Collider>>, 4>& new_collisions);
	};
}
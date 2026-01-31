#pragma once
#include <terme/entities/game_object.h>
#include <unordered_set>
#include <array>
#include <memory>	

namespace terme
{
	class Collider : public GameObject
	{
		friend class Simulation;

		//---------------------------------------------------------- fields

	protected:
		std::array<std::list<std::weak_ptr<Collider>>, 4> collisions_;

		//---------------------------------------------------------- methods
	public:
		using GameObject::GameObject;

	protected:

		virtual void OnCollisionEnter(std::shared_ptr<Collider> other, Direction collision_dir) {}
		virtual void OnCollisionExit(Direction ending_collision_dir) {}

	private:
		void CalledBySimNotifyCollisionEnter(std::unordered_set<std::shared_ptr<Collider>>colliding_objects, Direction collision_dir);
		void CalledBySimNotifyCollisionEnter(std::shared_ptr<Collider> colliding_object, Direction collision_dir);
		void CalledBySimUpdateEndedCollisions(const std::array<std::unordered_set<std::shared_ptr<Collider>>, 4>& new_collisions);
	};
}
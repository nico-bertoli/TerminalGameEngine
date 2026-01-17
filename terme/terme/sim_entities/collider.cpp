#include <terme/sim_entities/collider.h>
#include <terme/managers/time_manager.h>
#include <terme/core/simulation.h>
#include <terme/utils/smart_pointers_list_utils.h>

using std::weak_ptr;
using std::shared_ptr;
using std::list;
using std::unordered_set;

namespace terme
{
	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(unordered_set<shared_ptr<Collider>>colliding_objects, Direction collision_dir)
	{
		list<weak_ptr<Collider>>& local_direction_coll = collisions_[collision_dir];
		for (auto obj : colliding_objects)
		{
			if(smart_pointers_list_utils::WeakPtrListContainsShared(local_direction_coll, obj) == false)
			{
				local_direction_coll.push_back(obj);
				OnCollisionEnter(obj, collision_dir);
			}
		}
	}

	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(shared_ptr<Collider> colliding_object, Direction collision_dir)
	{
		CALLED_BY_SIM_NotifyCollisionEnter(unordered_set<shared_ptr<Collider>>{colliding_object}, collision_dir);
	}

	void Collider::CALLED_BY_SIM_UpdateEndedCollisions(const std::array<unordered_set<shared_ptr<Collider>>,4>& new_collisions)
	{
		for (int i = 0; i < new_collisions.size(); ++i)
		{
			list<weak_ptr<Collider>>& local_direction_coll = collisions_[i];
			const unordered_set<shared_ptr<Collider>>& new_direction_coll = new_collisions[i];

			list<weak_ptr<Collider>> to_remove;

			//update collision direction
			for (weak_ptr<Collider> collider_weak : local_direction_coll)
			{
				auto collider = collider_weak.lock();
				if (collider == nullptr || new_direction_coll.find(collider) == new_direction_coll.end())
					to_remove.push_back(collider_weak);
			}	

			for (auto to_remove_obj : to_remove)
				smart_pointers_list_utils::RemoveWeakPointerFromList(local_direction_coll, to_remove_obj);

			//call on collision exit
			if (to_remove.size() > 0)
				OnCollisionExit(static_cast<Direction>(i));
		}
	}
}
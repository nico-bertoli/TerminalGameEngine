#include <terme/entities/collider.h>
#include <terme/managers/time_manager.h>
#include <terme/core/simulation.h>

using std::weak_ptr;
using std::shared_ptr;
using std::list;
using std::unordered_set;

namespace terme
{
	//---------------------------- local utility methods
	template<typename T>
	bool WeakPtrListContainsShared(const std::list<std::weak_ptr<T>>& list, const std::shared_ptr<T>& sharedPtr)
	{
		for (const auto& weakItem : list)
			if (auto sharedItem = weakItem.lock())
				if (sharedItem == sharedPtr)
					return true;

		return false;
	}

	template<typename T>
	void RemoveWeakPointerFromList(std::list<std::weak_ptr<T>>& weakList, const std::weak_ptr<T>& targetWeak)
	{
		std::shared_ptr<T> target = targetWeak.lock();
		if (target == nullptr)
			return;

		for (auto itWeak = weakList.begin(); itWeak != weakList.end(); ++itWeak)
		{
			if (auto it = itWeak->lock())
				if (it == target)
				{
					weakList.erase(itWeak);
					return;
				}
		}
	}
	//----------------------------

	void Collider::CalledBySimNotifyCollisionEnter(unordered_set<shared_ptr<Collider>>colliding_objects, Direction collision_dir)
	{
		list<weak_ptr<Collider>>& local_direction_coll = collisions_[collision_dir];
		for (auto obj : colliding_objects)
		{
			if(WeakPtrListContainsShared(local_direction_coll, obj) == false)
			{
				local_direction_coll.push_back(obj);
				OnCollisionEnter(obj, collision_dir);
			}
		}
	}

	void Collider::CalledBySimNotifyCollisionEnter(shared_ptr<Collider> colliding_object, Direction collision_dir)
	{
		CalledBySimNotifyCollisionEnter(unordered_set<shared_ptr<Collider>>{colliding_object}, collision_dir);
	}

	void Collider::CalledBySimUpdateEndedCollisions(const std::array<unordered_set<shared_ptr<Collider>>,4>& new_collisions)
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
				RemoveWeakPointerFromList(local_direction_coll, to_remove_obj);

			//call on collision exit
			if (to_remove.size() > 0)
				OnCollisionExit(static_cast<Direction>(i));
		}
	}
}
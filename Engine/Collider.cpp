#include "Collider.h"
#include "TimeHelper.h"
#include "Simulation.h"
#include "SmartPointersListUtils.h"

using std::weak_ptr;
using std::shared_ptr;
using std::list;
using std::unordered_set;

namespace Engine
{
	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(unordered_set<shared_ptr<Collider>>collidingObjects, Direction collisionDir)
	{
		list<weak_ptr<Collider>>& localDirectionColl = collisions[collisionDir];
		for (auto obj : collidingObjects)
		{
			if(SmartPointersListUtils::WeakPtrListContainsShared(localDirectionColl, obj) == false)
			{
				localDirectionColl.push_back(obj);
				OnCollisionEnter(obj, collisionDir);
			}
		}
	}

	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(shared_ptr<Collider> collidingObject, Direction collisionDir)
	{
		CALLED_BY_SIM_NotifyCollisionEnter(unordered_set<shared_ptr<Collider>>{collidingObject}, collisionDir);
	}

	void Collider::CALLED_BY_SIM_UpdateEndedCollisions(const std::array<unordered_set<shared_ptr<Collider>>,4>& newCollisions)
	{
		for (int i = 0; i < newCollisions.size(); ++i)
		{
			list<weak_ptr<Collider>>& localDirectionColl = collisions[i];
			const unordered_set<shared_ptr<Collider>>& newDirectionColl = newCollisions[i];

			list<weak_ptr<Collider>> toRemove;

			//update collision direction
			for (weak_ptr<Collider> colliderWeak : localDirectionColl)
			{
				auto collider = colliderWeak.lock();
				if (collider == nullptr || newDirectionColl.find(collider) == newDirectionColl.end())
					toRemove.push_back(colliderWeak);
			}	

			for (auto toRemoveObj : toRemove)
				SmartPointersListUtils::RemoveWeakPointerFromList(localDirectionColl, toRemoveObj);

			//call on collision exit
			if (toRemove.size() > 0)
				OnCollisionExit(static_cast<Direction>(i));
		}
	}
}
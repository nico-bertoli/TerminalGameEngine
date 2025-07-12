#pragma once


namespace SmartPointersListUtils
{
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
}
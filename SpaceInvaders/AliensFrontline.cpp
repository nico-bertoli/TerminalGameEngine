#include "AliensFrontline.h"
#include "Alien.h"

using std::weak_ptr;
using std::shared_ptr;
using Engine::Vector2D;

namespace SpaceInvaders
{
	size_t AliensFrontline::GetMinY()
	{
		size_t min = SIZE_MAX;
		for (weak_ptr<Alien> alienWeak : frontLine)
		{
			shared_ptr<Alien> alien = alienWeak.lock();
			if (alien != nullptr && alien->GetPosY() < min)
				min = alien->GetPosY();
		}
		return min;
	}

	void AliensFrontline::ReplaceDestroyedElement(shared_ptr<Alien> destroyedAlien, const Vector2D<weak_ptr<Alien>>& aliensGrid)
	{
		size_t destroyedX = destroyedAlien->GetIndexInGridX();

		//try find new front line element
		for (int y = static_cast<int>(aliensGrid.GetSizeY()) - 1; y >= 0; --y)
		{
			shared_ptr<Alien> newCandidate = aliensGrid.Get(destroyedX, y).lock();
			if (newCandidate != nullptr && newCandidate != destroyedAlien)
			{
				frontLine[destroyedX] = newCandidate;
				return;
			}
		}
	}

	shared_ptr<Alien> AliensFrontline::GetRandom()
	{
		return GetAt(RandomUtils::GetRandomInt(0, static_cast<int>(frontLine.size()) - 1));
	}
}
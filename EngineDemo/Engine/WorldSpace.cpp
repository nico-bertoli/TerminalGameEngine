#include "WorldSpace.h"
#include "Collider.h"

using std::shared_ptr;
using std::unordered_set;

namespace Engine
{
	shared_ptr<FakeCollider> WorldSpace::WORLD_MARGIN = std::make_shared<FakeCollider>();
	shared_ptr<FakeCollider> WorldSpace::SCREEN_MARGIN = std::make_shared<FakeCollider>();

	void WorldSpace::Init(int xSize, int ySize, size_t screenPadding)
	{
		space.Clear();
		space.Resize(xSize, ySize);

		for (Cell cell : space)
			cell.objects.clear();
			
		this->screenPadding = screenPadding;
	}

	void WorldSpace::InsertObject(shared_ptr<GameObject> obj)
	{
		WriteSpace(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), obj);
	}

	void WorldSpace::RemoveObject(shared_ptr<GameObject> obj)
	{
		EraseSpace(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), obj);
	}

	void WorldSpace::MoveObject(shared_ptr<GameObject> obj, Direction direction)
	{
		switch (direction)
		{
		case Direction::up:
		{
			int yWrite = obj->GetMaxPosY() + 1;
			int yClear = obj->GetPosY();
			WriteSpace(obj->GetPosX(), yWrite, obj->GetModelWidth(), 1, obj);
			EraseSpace(obj->GetPosX(), yClear, obj->GetModelWidth(), 1, obj);
			break;
		}
		case Direction::down:
		{
			int yWrite = obj->GetPosY() - 1;
			int yClear = obj->GetMaxPosY();
			WriteSpace(obj->GetPosX(), yWrite, obj->GetModelWidth(), 1, obj);
			EraseSpace(obj->GetPosX(), yClear, obj->GetModelWidth(), 1, obj);
			break;
		}
		case Direction::right:
		{
			int xWrite = obj->GetMaxPosX() + 1;
			int xClear = obj->GetPosX();
			WriteSpace(xWrite, obj->GetPosY(), 1, obj->GetModelHeight(), obj);
			EraseSpace(xClear, obj->GetPosY(), 1, obj->GetModelHeight(), obj);
			break;
		}

		case Direction::left:
		{
			int xWrite = obj->GetPosX() - 1;
			int xClear = obj->GetMaxPosX();
			WriteSpace(xWrite, obj->GetPosY(), 1, obj->GetModelHeight(), obj);
			EraseSpace(xClear, obj->GetPosY(), 1, obj->GetModelHeight(), obj);
			break;
		}
		}
	}

	void WorldSpace::WriteSpace(int xStart, int yStart, size_t width, size_t height, shared_ptr<GameObject> obj)
	{
		assert(obj != nullptr);

		for (int y = yStart; y < yStart + height; ++y)
			for (int x = xStart; x < xStart + width; ++x)
			{
				Cell& cell = space.Get(x, y);

				GameObject::InsertInListUsingRule
				(
					obj, 
					cell.objects ,
					// add high sorting layer objects at top of list
					[](shared_ptr<GameObject> newItem, shared_ptr<GameObject> listItem){ return newItem->GetSortingLayer() >= listItem->GetSortingLayer();}
				);

				shared_ptr<Collider> objCollider = std::dynamic_pointer_cast<Collider>(obj);
				if (objCollider)
				{
					assert(cell.collider.expired() || cell.collider.lock() == objCollider);
					cell.collider = objCollider;
				}
			}
	}

	void WorldSpace::EraseSpace(int xStart, int yStart, size_t width, size_t height, shared_ptr<GameObject> obj)
	{
		assert(obj != nullptr);

		for (int y = yStart; y < yStart + height; ++y)
			for (int x = xStart; x < xStart + width; ++x)
			{
				Cell& cell = space.Get(x, y);

				//------------------ erase from cell.objects
				for (auto it = cell.objects.begin(); it != cell.objects.end(); ++it)
				{
					auto itSharedPt = it->lock();
					if (itSharedPt != nullptr && itSharedPt == obj)
					{
						cell.objects.erase(it);
						break;
					}
				}

				//------------------ erase collider
				shared_ptr<Collider> objCollider = std::dynamic_pointer_cast<Collider>(obj);
				if (objCollider)
				{
					assert(cell.collider.expired() || cell.collider.lock() == objCollider);
					cell.collider.reset();
				}
			}
	}

	bool WorldSpace::IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height, unordered_set<shared_ptr<Collider>>& outAreaObjects) const
	{
		for (int y = startingY; y < startingY + height; ++y)
		{
			for (int x = startingX; x < startingX + width; ++x)
			{
				auto cellCollider = space.Get(x, y).collider.lock();
				if (IsCoordinateInsideSpace(x, y) && cellCollider != nullptr)
					outAreaObjects.insert(cellCollider);
			}
		}

		return outAreaObjects.size() == 0;
	}

	bool WorldSpace::IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height) const
	{
		for (int y = startingY; y < startingY + height; ++y)
			for (int x = startingX; x < startingX + width; ++x)
				if (IsCoordinateInsideSpace(x, y) && space.Get(x, y).collider.expired() == false)
					return false;

		return true;
	}


	bool WorldSpace::IsCoordinateInsideSpace(int xPos, int yPos) const
	{
		return IsInsideSpaceX(xPos) && IsInsideSpaceY(yPos);
	}


	bool WorldSpace::IsInsideSpaceX(int xPos) const
	{
		return xPos >= 0 && xPos < space.GetSizeX();
	}

	bool WorldSpace::IsInsideSpaceY(int yPos) const
	{
		return yPos >= 0 && yPos < space.GetSizeY();
	}

	bool WorldSpace::CanObjectMoveAtDirection
	(
		shared_ptr<const GameObject> object,
		Direction direction,
		unordered_set<shared_ptr<Collider>>& collidingObjects
	) const
	{
		shared_ptr<const Collider> colliderObj = std::dynamic_pointer_cast<const Collider>(object);

		switch (direction)
		{
		case Direction::up:
		{
			int movingToY = object->GetMaxPosY() + 1;

			//exiting world
			if (movingToY == space.GetSizeY())
			{
				collidingObjects.insert(WORLD_MARGIN);
				return false;
			}

			//exiting screen space
			if ((object->CanExitScreenSpace() == false) && (movingToY == space.GetSizeY() - screenPadding))
			{
				collidingObjects.insert(SCREEN_MARGIN);
				return false;
			}

			//obj collision
			if (colliderObj != nullptr && IsCollidersAreaEmpty(colliderObj->GetPosX(), movingToY, colliderObj->GetModelWidth(), 1, collidingObjects) == false)
				return false;

			return true;
		}
		case Direction::down:
		{
			int movingToY = object->GetPosY() - 1;

			//exiting world
			if (movingToY == -1)
			{
				collidingObjects.insert(WORLD_MARGIN);
				return false;
			}

			//exiting screen space
			if ((object->CanExitScreenSpace() == false) && (movingToY == screenPadding - 1))
			{
				collidingObjects.insert(SCREEN_MARGIN);
				return false;
			}

			//obj collision
			if (colliderObj != nullptr && IsCollidersAreaEmpty(colliderObj->GetPosX(), movingToY, colliderObj->GetModelWidth(), 1, collidingObjects) == false)
				return false;

			return true;
		}
		case Direction::right:
		{
			int movingToX = object->GetMaxPosX() + 1;

			//exiting world
			if (movingToX == space.GetSizeX())
			{
				collidingObjects.insert(WORLD_MARGIN);
				return false;
			}

			//exiting screen space
			if ((object->CanExitScreenSpace() == false) && (movingToX == space.GetSizeX() - screenPadding))
			{
				collidingObjects.insert(SCREEN_MARGIN);
				return false;
			}

			//obj collision
			if (colliderObj != nullptr && IsCollidersAreaEmpty(movingToX, colliderObj->GetPosY(), 1, colliderObj->GetModelHeight(), collidingObjects) == false)
				return false;

			return true;
		}
		case Direction::left:
		{
			int movingToX = object->GetPosX() - 1;

			//exiting world
			if (movingToX == -1)
			{
				collidingObjects.insert(WORLD_MARGIN);
				return false;
			}

			//exiting screen space
			if ((object->CanExitScreenSpace() == false) && (movingToX == screenPadding - 1))
			{
				collidingObjects.insert(SCREEN_MARGIN);
				return false;
			}

			//obj collision
			if (colliderObj != nullptr && IsCollidersAreaEmpty(movingToX, colliderObj->GetPosY(), 1, colliderObj->GetModelHeight(), collidingObjects) == false)
				return false;

			return true;
		}
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	unordered_set<shared_ptr<GameObject>> WorldSpace::GetAreaTopLayerObjects(shared_ptr<GameObject> obj)
	{
		return GetAreaTopLayerObjects(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight());
	}

	unordered_set<shared_ptr<GameObject>> WorldSpace::GetAreaTopLayerObjects(int startingX, int startingY, size_t width, size_t height)
	{
		unordered_set<shared_ptr<GameObject>> objects;
		for (int y = startingY; y < startingY + height; ++y)
		{
			for (int x = startingX; x < startingX + width; ++x)
			{
				Cell& cell = space.Get(x, y);
				if (cell.objects.size() > 0)
				{
					auto topItem = space.Get(x, y).objects.begin();
					while (topItem != space.Get(x, y).objects.end())
					{
						auto topItemSp = topItem->lock();
						if (topItemSp != nullptr)
						{
							objects.insert(topItemSp);
							break;
						}	
					}
				}
			}
		}
		return objects;
	}
}
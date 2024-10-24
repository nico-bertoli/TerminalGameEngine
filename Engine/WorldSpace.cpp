#include "WorldSpace.h"
#include "Collider.h"

namespace Engine
{
	FakeCollider WorldSpace::WORLD_MARGIN_MEMORY;
	FakeCollider WorldSpace::SCREEN_MARGIN_MEMORY;

	FakeCollider* WorldSpace::WORLD_MARGIN = &WorldSpace::WORLD_MARGIN_MEMORY;
	FakeCollider* WorldSpace::SCREEN_MARGIN = &WorldSpace::SCREEN_MARGIN_MEMORY;

	void WorldSpace::Init(int xSize, int ySize, size_t screenPadding)
	{
		space.Clear();
		space.Resize(xSize, ySize);

		for (Cell cell : space)
		{
			cell.collider = nullptr;
			cell.objects.clear();
		}
			
		this->screenPadding = screenPadding;
	}

	void WorldSpace::InsertObject(GameObject* obj)
	{
		WriteSpace(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), obj);
	}

	void WorldSpace::RemoveObject(GameObject* obj)
	{
		EraseSpace(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), obj);
	}

	void WorldSpace::MoveObject(GameObject* obj, Direction direction)
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

	void WorldSpace::WriteSpace(int xStart, int yStart, size_t width, size_t height, GameObject* obj)
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
					[](GameObject* newItem, GameObject* listItem){ return newItem->GetSortingLayer() >= listItem->GetSortingLayer();} 
				);

				Collider* objCollider = dynamic_cast<Collider*>(obj);
				if (objCollider)
				{
					assert(cell.collider == nullptr || cell.collider == objCollider);

					cell.collider = objCollider;
				}
			}
	}

	void WorldSpace::EraseSpace(int xStart, int yStart, size_t width, size_t height, GameObject* obj)
	{
		assert(obj != nullptr);

		for (int y = yStart; y < yStart + height; ++y)
			for (int x = xStart; x < xStart + width; ++x)
			{
				Cell& cell = space.Get(x, y);

				//------------------ erase from cell.objects
				for (auto it = cell.objects.begin(); it != cell.objects.end(); ++it)
				{
					if (*it == obj)
					{
						cell.objects.erase(it);
						break;
					}
				}

				//------------------ erase collider
				Collider* objCollider = dynamic_cast<Collider*>(obj);
				if (objCollider)
				{
					assert(cell.collider == nullptr || cell.collider == objCollider);
					cell.collider = nullptr;
				}
			}
	}

	bool WorldSpace::IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height, uset<Collider*>& areaObjects) const
	{
		for (int y = startingY; y < startingY + height; ++y)
		{
			for (int x = startingX; x < startingX + width; ++x)
			{
				Collider* cellCollider = space.Get(x, y).collider;
				if (IsCoordinateInsideSpace(x, y) && cellCollider != nullptr)
					areaObjects.insert(cellCollider);
			}
		}

		return areaObjects.size() == 0;
	}

	bool WorldSpace::IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height) const
	{
		for (int y = startingY; y < startingY + height; ++y)
			for (int x = startingX; x < startingX + width; ++x)
				if (IsCoordinateInsideSpace(x, y) && space.Get(x, y).collider != nullptr)
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
		const GameObject* object,
		Direction direction,
		uset<Collider*>& collidingObjects
	) const
	{
		const Collider* colliderObj = dynamic_cast<const Collider*>(object);

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

	uset<GameObject*> WorldSpace::GetAreaTopLayerObjects(GameObject* obj)
	{
		return GetAreaTopLayerObjects(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight());
	}

	uset<GameObject*> WorldSpace::GetAreaTopLayerObjects(int startingX, int startingY, size_t width, size_t height)
	{
		uset<GameObject*> objects;
		for (int y = startingY; y < startingY + height; ++y)
		{
			for (int x = startingX; x < startingX + width; ++x)
			{
				Cell& cell = space.Get(x, y);
				if (cell.objects.size() > 0)
					objects.insert(*space.Get(x, y).objects.begin());
			}
		}
		return objects;
	}
}
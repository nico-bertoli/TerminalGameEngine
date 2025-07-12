#pragma once
#include "DirectionUtils.h"
#include "FakeCollider.h"
#include "Vector2D.h"
#include <memory>

#include <cassert>
#include <unordered_set>
#include <set>

namespace Engine
{
	class WorldSpace
	{
		//---------------------------------------------------------- Structs
	private:
		struct Cell
		{
			// cell collider, max 1 for cell
			std::weak_ptr<Collider> collider;	

			// all objects in cell, including collider if present
			// (using list cause there are a lot of small sets (2/3 elements max per list usually)
			std::list<std::weak_ptr<GameObject>> objects;
		};

		//---------------------------------------------------------- Margins
	public:
		static std::shared_ptr<FakeCollider> WORLD_MARGIN;
		static std::shared_ptr<FakeCollider> SCREEN_MARGIN;

		//---------------------------------------------------------- Fields
	public:
		Vector2D<Cell> space;
		size_t screenPadding;
		//---------------------------------------------------------- Methods
	public:
		void Init(int xSize, int ySize, size_t screenPadding);

		bool CanObjectMoveAtDirection(std::shared_ptr<const GameObject> obj, Direction direction, std::unordered_set<std::shared_ptr<Collider>>& collidingObjects) const;
		void InsertObject(std::shared_ptr<GameObject> obj);
		void RemoveObject(std::shared_ptr<GameObject> obj);
		void MoveObject(std::shared_ptr<GameObject> obj, Direction direction);
		bool IsCoordinateInsideSpace(int xPos, int yPos) const;
		bool IsInsideSpaceX(int xPos) const;
		bool IsInsideSpaceY(int yPos) const;

		bool IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height, std::unordered_set<std::shared_ptr<Collider>>& outAreaObjects) const;
		bool IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height) const;

		std::unordered_set<std::shared_ptr<GameObject>> GetAreaTopLayerObjects(std::shared_ptr<GameObject> obj);
		std::unordered_set<std::shared_ptr<GameObject>> GetAreaTopLayerObjects(int startingX, int startingY, size_t width, size_t height);

	private:
		void WriteSpace(int xStart, int yStart, size_t width, size_t height, std::shared_ptr<GameObject> value);
		void EraseSpace(int xStart, int yStart, size_t width, size_t height, std::shared_ptr<GameObject> value);
	};
}
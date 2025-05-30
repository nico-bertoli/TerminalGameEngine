#pragma once
#include "RandomUtils.h"
#include "Vector2D.h"
#include <vector>

namespace SpaceInvaders
{
	class Alien;

	class AliensFrontline
	{
	private:
		std::vector<std::weak_ptr<Alien>> frontLine;
	public:
		void Init(size_t size) { frontLine.resize(size); }
		std::shared_ptr<Alien> GetAt(size_t pos) { return frontLine.size() > 0 ? frontLine[pos].lock() : nullptr; }
		std::shared_ptr<Alien> GetRandom();
		void Set(size_t pos, std::shared_ptr<Alien> alien) { frontLine[pos] = alien; }
		size_t GetMinY();
		void ReplaceDestroyedElement(std::shared_ptr<Alien> destroyedAlien, const Engine::Vector2D<std::weak_ptr<Alien>>& aliensGrid);
	};
}
#include "SortingLayerTestObject.h"

using Engine::Direction;

namespace Platformer
{
	SortingLayerTestObject::SortingLayerTestObject
	(
		int xPos,
		int yPos,
		size_t sizeX,
		size_t sizeY,
		char modelChar,
		int color,
		size_t sortingLayer,
		double moveSpeed,
		std::optional<Direction> mainDirection
	) 
		: 
		GameObject(xPos, yPos),
		sizeX(sizeX),
		sizeY(sizeY),
		modelChar(modelChar),
		color(color),
		sortingLayer(sortingLayer),
		moveSpeed(moveSpeed),
		mainDirection(mainDirection){ }

	void SortingLayerTestObject::InitModel()
	{
		model = CreteModelUsingChar(modelChar, sizeX, sizeY);
		SetModel(model);
	}

	void SortingLayerTestObject::Update()
	{

	}
}
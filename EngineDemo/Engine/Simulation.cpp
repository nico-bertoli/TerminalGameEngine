#include "Simulation.h"
#include "Collider.h"
#include "ISimulationEntity.h"
#include "GameObject.h"
#include "Level.h"
#include "TimeHelper.h"
#include "WorldSpace.h"
#include "DebugManager.h"
#include "RandomUtils.h"
#include "Particle.h"

#include <Windows.h>
#include <cassert>
#include <stdexcept>
#include <array>

using std::shared_ptr;
using std::weak_ptr;
using std::unordered_set;
using std::list;

namespace Engine
{
	size_t Simulation::GetWorldSizeX() const { return level->GetWorldSizeX(); }
	size_t Simulation::GetWorldSizeY() const { return level->GetWorldSizeY(); }
	size_t Simulation::GetScreenPadding() const { return level->GetScreenPadding(); }
	size_t Simulation::GetScreenSizeX() const { return level->GetWorldSizeX() - 2 * level->GetScreenPadding(); }
	size_t Simulation::GetScreenSizeY() const { return level->GetWorldSizeY() - 2 * level->GetScreenPadding(); }
	shared_ptr<Level> Simulation::GetActiveLevel() { return level; }
	UIPrinter& Simulation::GetUIPrinter() { return *uiPrinter; }

	void Simulation::SpawnParticles
	(
		int posX,
		int posY,
		size_t width,
		size_t height,
		char modelChar,
		int color,
		double speed,
		size_t movementLifeTime,
		double density,
		std::optional<Direction> mainDirection
	)
	{
		int densityIntPart = static_cast<int>(density);
		double densityDecimalPart = density - densityIntPart;

		for (int y = posY; y < posY + height; ++y)
		{
			for (int x = posX; x < posX + width; ++x)
			{
				//add particles depending on density int part
				for (int density = 0; density <= densityIntPart; ++density)
				{
					//add particles depending on density fractional part
					if (density == densityIntPart && RandomUtils::GetRandomDouble(0, 1) > densityDecimalPart)
						continue;

					shared_ptr<Particle> particle = std::make_shared<Particle>(x, y, modelChar, color, speed, movementLifeTime, mainDirection);
					TryAddEntity(particle);
				}
			}
		}
	}

	void Simulation::Step()
	{
		if (level->IsTerminated())
			return;

		if (level->IsPostGameOverPauseEnded())
		{
			level->Update();
			return;
		}

		moveRequests.clear();

		UpdateAllEntities();

		ExecuteMoveRequests();

		RemoveMarkedEntities();

		UpdateAllObjectsEndedCollisions();

		PrintObjects();

		OnFrameGenerated.Notify();

#if DEBUG_MODE && SHOW_FPS
		DebugManager::Instance().ShowAverageFPS();
#endif
	}

	void Simulation::RequestMovement(shared_ptr<GameObject> applicantObj, Direction moveDir, double moveSpeed)
	{
		if (IsEntityInSimulation(applicantObj) == false)
		{
			std::cerr << "object requesting movement but it's not in simulation";
			return;
		}

		MoveRequest request(applicantObj, moveDir, moveSpeed);
		EnqueueMoveRequestSortingBySpeed(request);
	}

	void Simulation::EnqueueMoveRequestSortingBySpeed(MoveRequest request)
	{
		auto it = moveRequests.begin();
		while (it != moveRequests.end())
		{
			if (it->moveSpeed > request.moveSpeed)
				break;
			++it;
		}
		moveRequests.insert(it, request);
	}

	void Simulation::RemoveMarkedEntities()
	{
		for (weak_ptr<ISimulationEntity>& entity : toRemoveEntities)
		{
			shared_ptr<ISimulationEntity> entitySp = entity.lock();
			if (entitySp != nullptr)
			{
				shared_ptr<GameObject> objectEntity = std::dynamic_pointer_cast<GameObject>(entitySp);
				if (objectEntity != nullptr)
				{
					objectEntity->OnDestroy();
					simulationPrinter->ClearObject(objectEntity);
					worldSpace.RemoveObject(objectEntity);
					MarkAreaToReprint(objectEntity);
				}
				entities.erase(entitySp);
			}
		}
		toRemoveEntities.clear();
	}

	void Simulation::RemoveEntity(shared_ptr<ISimulationEntity> entity)
	{
		if (entity == nullptr)
			return;

		if (!IsEntityInSimulation(entity))
			return;

		//entity will be removed at proper stage of step
		toRemoveEntities.push_back(entity);
	}

	void Simulation::UpdateAllEntities()
	{
		level->Update();
		for (shared_ptr<ISimulationEntity> entity : entities)
			entity->Update();
	}

	void Simulation::ExecuteMoveRequests()
	{
		
		for (auto it = moveRequests.begin(); it != moveRequests.end(); ++it)
		{

			shared_ptr<GameObject> obj = it->object.lock();
			if (obj == nullptr)
				continue;

			int oldPosX = obj->GetPosX();
			int oldPosY = obj->GetPosY();

			if (TryMoveObjectAtDirection(obj, it->moveDir))
			{
				simulationPrinter->ClearArea(oldPosX, oldPosY, obj->GetModelWidth(), obj->GetModelHeight());
				MarkAreaToReprintAfterMovement(obj, oldPosX, oldPosY);
			}
		}
	}

	void Simulation::PrintObjects()
	{
		list<shared_ptr<GameObject>> toBePrintedObjects;

		//create sorted list
		for (shared_ptr<ISimulationEntity> entity : entities)
		{
			shared_ptr<GameObject> objEntity = std::dynamic_pointer_cast<GameObject>(entity);
			if (objEntity && objEntity->mustBeReprinted)
				GameObject::InsertInListUsingRule
				(
					objEntity, toBePrintedObjects,
					[](shared_ptr<GameObject> toInsertObj, shared_ptr<GameObject> listObject) { return  toInsertObj->GetSortingLayer() <= listObject->GetSortingLayer(); }
				);
		}

		if (toBePrintedObjects.size() > 1)
			int tododelete = 2;

		//print objects
		for (auto obj : toBePrintedObjects)
		{
			simulationPrinter->PrintObject(obj);
			UnmarkObjectToReprint(obj);
		}
	}


	void Simulation::UpdateAllObjectsEndedCollisions()
	{
		for (auto& entity : entities)
		{
			shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(entity);
			if (collider != nullptr)
				UpdateObjectEndedCollisions(collider);
		}
	}

	void Simulation::UpdateObjectEndedCollisions(shared_ptr<Collider> collider)
	{
		int xPos = collider->GetPosX();
		int yPos = collider->GetPosY();
		int xMax = collider->GetMaxPosX();
		int yMax = collider->GetMaxPosY();
		size_t width = collider->GetModelWidth();
		size_t height = collider->GetModelHeight();
		bool canExitScreen = collider->CanExitScreenSpace();

		std::array<unordered_set<shared_ptr<Collider>>, 4> collisions;

		//screen collisions
		if (!canExitScreen && !IsCoordinateInsideScreenSpace(xPos, yMax + 1))
			collisions[Direction::up].insert(WorldSpace::SCREEN_MARGIN);
		if (!canExitScreen && !IsCoordinateInsideScreenSpace(xPos, yPos - 1))
			collisions[Direction::down].insert(WorldSpace::SCREEN_MARGIN);
		if (!canExitScreen && !IsCoordinateInsideScreenSpace(xMax + 1, yPos))
			collisions[Direction::right].insert(WorldSpace::SCREEN_MARGIN);
		if (!canExitScreen && !IsCoordinateInsideScreenSpace(xPos - 1, yPos))
			collisions[Direction::left].insert(WorldSpace::SCREEN_MARGIN);

		// object-object collisions
		worldSpace.IsCollidersAreaEmpty(xPos, yMax + 1, width, 1, collisions[Direction::up]);
		worldSpace.IsCollidersAreaEmpty(xPos, yPos - 1, width, 1, collisions[Direction::down]);
		worldSpace.IsCollidersAreaEmpty(xPos - 1, yPos, 1, height, collisions[Direction::left]);
		worldSpace.IsCollidersAreaEmpty(xMax + 1, yPos, 1, height, collisions[Direction::right]);

		collider->CALLED_BY_SIM_UpdateEndedCollisions(collisions);
	}

	bool Simulation::TryAddEntity(shared_ptr<ISimulationEntity> entity)
	{
		shared_ptr<GameObject> objectEntity = std::dynamic_pointer_cast<GameObject>(entity);

		if (objectEntity != nullptr)
			objectEntity->Init();

		if (!CanEntityBeAdded(entity))
			return false;
		
		if(objectEntity != nullptr)
			worldSpace.InsertObject(objectEntity);

		entities.insert(entity);
		return true;
	}

	bool Simulation::CanEntityBeAdded(shared_ptr<ISimulationEntity> entity) const
	{
		if (IsEntityInSimulation(entity))
			return false;

		shared_ptr<const Collider> collider = std::dynamic_pointer_cast<const Collider>(entity);
		if (collider != nullptr)
		{
			return worldSpace.IsCollidersAreaEmpty
			(
				collider->GetPosX(),
				collider->GetPosY(),
				collider->GetModelWidth(),
				collider->GetModelHeight()
			);
		}
		else
			return true;
	}

	bool Simulation::IsEntityInSimulation(shared_ptr<ISimulationEntity> newEntity) const
	{
		auto it = entities.find(newEntity);
		return it != entities.end();
	}

	bool Simulation::TryMoveObjectAtDirection(shared_ptr<GameObject> obj, Direction direction)
	{
		unordered_set<shared_ptr<Collider>> outCollidingObjects;

		shared_ptr<Collider> colliderObj = std::dynamic_pointer_cast<Collider>(obj);

		if (worldSpace.CanObjectMoveAtDirection(obj, direction, outCollidingObjects) == false)
		{
			//remove entity if trying to move out of world space
			if (outCollidingObjects.find(WorldSpace::WORLD_MARGIN) != outCollidingObjects.end())
			{
				RemoveEntity(obj);
			}
			else
			{
				if (colliderObj != nullptr)
				{
					colliderObj->CALLED_BY_SIM_NotifyCollisionEnter(outCollidingObjects, direction);

					for (auto collidingObj : outCollidingObjects)
						if (collidingObj != WorldSpace::SCREEN_MARGIN)
							collidingObj->CALLED_BY_SIM_NotifyCollisionEnter(colliderObj, DirectionUtils::GetInverseDirection(direction));
				}
			}
			return false;
		}

		worldSpace.MoveObject(obj, direction);

		obj->CALLED_BY_SIM_Move(direction);

		return true;
	}

	void Simulation::LoadLevel(shared_ptr<Level> level)
	{
		this->level = level;

		entities.clear();
		worldSpace.Init(level->GetWorldSizeX(), level->GetWorldSizeY(), level->GetScreenPadding());

#if DEBUG_MODE
		DebugManager::Instance().Reset(GetScreenSizeX(), GetScreenSizeY(), GetScreenPadding());
#endif

		ResetPrinters(level);
		level->LoadInSimulation();
	}

	void Simulation::ResetPrinters(shared_ptr<const Level> level)
	{
		Terminal::Instance().Clear();

		simulationPrinter = std::make_unique<SimulationPrinter>
			(
				GetScreenSizeX(),
				GetScreenSizeY(),
				GetScreenPadding(),
				level->GetBackgroundColor(),
				level->GetBackgroundFileName()
			);

		uiPrinter.reset();
		uiPrinter = std::make_unique<UIPrinter>(GetScreenSizeX(), GetScreenSizeY(), GetScreenPadding(), level->GetMarginsColor());
	}

	bool Simulation::IsInsideScreenY(int yPos) const
	{
		return
			yPos >= GetScreenPadding() &&
			yPos < GetWorldSizeY() - GetScreenPadding();
	}
	bool Simulation::IsInsideScreenX(int xPos) const
	{
		return
			xPos >= GetScreenPadding() &&
			xPos < GetWorldSizeX() - GetScreenPadding();
	}

	void Simulation::MarkAreaToReprint(shared_ptr<GameObject> objArea)
	{
		std::unordered_set<shared_ptr<GameObject>> toBeReprintedObjects = worldSpace.GetAreaTopLayerObjects(objArea);
		for (shared_ptr<GameObject> obj : toBeReprintedObjects)
			obj->mustBeReprinted = true;
	}

	void Simulation::MarkAreaToReprintAfterMovement(shared_ptr<GameObject> obj, int oldPosX, int oldPosY)
	{
		// finding area = combination of old position area + new position area
		int minX = obj->GetPosX() < oldPosX ? obj->GetPosX() : oldPosX;
		int minY = obj->GetPosY() < oldPosY ? obj->GetPosY() : oldPosY;
		bool isMovementHorizontal = oldPosX != obj->GetPosX();
		size_t width = isMovementHorizontal ? obj->GetModelWidth() + 1 : obj->GetModelWidth();
		size_t height = !isMovementHorizontal ? obj->GetModelHeight() + 1 : obj->GetModelHeight();

		std::unordered_set<shared_ptr<GameObject>> toBeReprintedObjects = worldSpace.GetAreaTopLayerObjects(minX, minY, width, height);

		for (shared_ptr<GameObject> obj : toBeReprintedObjects)
			obj->mustBeReprinted = true;
	}
}
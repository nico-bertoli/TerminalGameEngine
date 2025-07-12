#pragma once

#include "Config.h"
#include "WorldSpace.h"
#include "UIPrinter.h"
#include "SimulationPrinter.h"
#include <list>
#include <unordered_set>
#include <optional>
#include <memory>

namespace Engine
{
	class Collider;
	class GameObject;
	class ISimulationEntity;
	class Frame;
	class SimulationPrinter;
	class UIPrinter;
	class Level;

	class Simulation : public Singleton<Simulation>
	{
		//------------------------------------------------------------------------------------ Friend Classes
		friend class Singleton;
		friend class GameObject;

		//------------------------------------------------------------------------------------ Structs
		struct MoveRequest
		{
			std::weak_ptr<GameObject> object;
			Direction moveDir;
			double moveSpeed;

			MoveRequest(std::shared_ptr<GameObject> object, Direction direction, double speed)
				:object(object), moveDir(direction), moveSpeed(speed){ }
		};

		//------------------------------------------------------------------------------------ Fields
	public:
		Event<> OnFrameGenerated;

	private:
		std::unique_ptr<SimulationPrinter> simulationPrinter;
		std::unique_ptr<UIPrinter> uiPrinter;
		std::shared_ptr<Level> level;
		WorldSpace worldSpace;
		std::unordered_set<std::shared_ptr<ISimulationEntity>> entities;
		std::list<std::weak_ptr<ISimulationEntity>> toRemoveEntities;

		// move requests are sorted from slower to faster
		// slower objects have to move before faster ones to prevent false collisions detection
		std::list<MoveRequest> moveRequests;

		//------------------------------------------------------------------------------------ Methods
	public:
		void LoadLevel(std::shared_ptr<Level> level);
		void Step();
		bool TryAddEntity(std::shared_ptr<ISimulationEntity> entity);
		void RemoveEntity(std::shared_ptr<ISimulationEntity> entity);
		void RequestMovement(std::shared_ptr<GameObject> applicantObj, Direction moveDir, double moveSpeed);
		size_t GetWorldSizeX() const;
		size_t GetWorldSizeY() const;
		size_t GetScreenPadding() const;
		size_t GetScreenSizeX() const;
		size_t GetScreenSizeY() const;
		std::shared_ptr<Level> GetActiveLevel();
		UIPrinter& GetUIPrinter();

		void SpawnParticles
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
			std::optional<Direction> mainDirection = std::nullopt
		);

	private:
		bool TryMoveObjectAtDirection(std::shared_ptr<GameObject> obj, Direction direction);
		bool CanEntityBeAdded(std::shared_ptr<ISimulationEntity> entity) const;
		bool IsEntityInSimulation(std::shared_ptr<ISimulationEntity> newEntity) const;
		void UpdateObjectEndedCollisions(std::shared_ptr<Collider> collidingObj);
		void ResetPrinters(std::shared_ptr<const Level> level);
		void EnqueueMoveRequestSortingBySpeed(MoveRequest request);
		void UpdateAllEntities();
		void ExecuteMoveRequests();
		void UpdateAllObjectsEndedCollisions();
		void PrintObjects();
		void RemoveMarkedEntities();

		bool IsInsideScreenX(int xPos) const;
		bool IsInsideScreenY(int yPos) const;
		bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const { return IsInsideScreenX(xPos) && IsInsideScreenY(yPos); }

		void MarkAreaToReprint(std::shared_ptr<GameObject> objArea);
		void MarkAreaToReprintAfterMovement(std::shared_ptr<GameObject> obj, int oldPosX, int oldPosY);
		void UnmarkObjectToReprint(std::shared_ptr<GameObject> obj) { obj->mustBeReprinted = false; }
	};
}

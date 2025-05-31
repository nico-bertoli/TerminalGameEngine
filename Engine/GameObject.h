#pragma once
#include "Config.h"
#include "DirectionUtils.h"
#include "ISimulationEntity.h"
#include "Terminal.h"
#include "Event.h"
#include "Vector2D.h"

#include <memory>
#include <Windows.h>

namespace Engine
{
	using Model = Vector2D<char>;

	class GameObject : public ISimulationEntity
	{
		friend class Simulation;

		//---------------------------------------------------------- Fields
	public:
		Event<std::weak_ptr<GameObject>, Direction> OnMove;
		// generic on destroy event could be added

	protected:
		bool canMove = true;

	private:
		int xPos;
		int yPos;

		double xPosContinuous;
		double yPosContinuous;

		/// never set this value directly, use simulation MarkObjectToReprint
		bool mustBeReprinted = true;
		const Model* model = nullptr;

		//---------------------------------------------------------- Methods
	public:
		GameObject(int xPos, int yPos);

		virtual int GetColor() const { return Terminal::WHITE; }
		virtual size_t GetSortingLayer() const { return 100; }
		void Init() { InitModel(); }
		int GetPosX() const { return xPos; }
		int GetPosY() const { return yPos; }
		int GetMaxPosX()const { return xPos + static_cast<int>(GetModelWidth()) - 1; }
		int GetMaxPosY()const { return yPos + static_cast<int>(GetModelHeight()) - 1; }
		int GetMidPosX() { return GetPosX() + static_cast<int>(GetModelWidth()) / 2; }
		int GetMidPosY() { return GetPosY() + static_cast<int>(GetModelHeight()) / 2; }
		size_t GetModelWidth()const { return model->GetSizeX(); };
		size_t GetModelHeight()const { return model->GetSizeY(); }
		const Model& GetModel()const { return *model; }
		virtual bool CanExitScreenSpace() const = 0;
		static void InsertInListUsingRule(std::shared_ptr<GameObject> obj, std::list<std::shared_ptr<GameObject>>& list, bool(*InsertRule)(std::shared_ptr<GameObject> newItem, std::shared_ptr<GameObject> listItem));
		static void InsertInListUsingRule(std::shared_ptr<GameObject> obj, std::list<std::weak_ptr<GameObject>>& list, bool(*InsertRule)(std::shared_ptr<GameObject> newItem, std::shared_ptr<GameObject> listItem));

	protected:
		virtual void InitModel() = 0;
		virtual double GetGravityScale() const = 0;
		virtual void OnDestroy() {} // called by simulation
		virtual void TryMove(Direction direction, double moveSpeed);
		void Update()override;
		Model CreteModelUsingChar(char modelChar, size_t sizeX, size_t sizeY) const;
		void SetModel(const Model& newModel);

	private:
		void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
		void ApplyGravity();
		void CALLED_BY_SIM_Move(Direction direction);
	};


}
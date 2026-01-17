#pragma once
#include "Config.h"
#include "Utils/DirectionUtils.h"
#include "SimEntities/ISimulationEntity.h"
#include "Terminal/Terminal.h"
#include "General/Vector2Int.h"
#include <nbase_kit/matrix.h>
#include <nbase_kit/event.h>

#include <list>
#include <memory>

namespace Engine
{
	using Model = nbase_kit::Matrix<char>;

	class GameObject : public ISimulationEntity
	{
		friend class Simulation;

		//---------------------------------------------------------- Fields
	public:
		nbase_kit::Event<std::weak_ptr<GameObject>, Direction> on_move;
		// generic on destroy event could be added

	protected:
		bool can_move_ = true;

	private:
		int x_pos_;
		int y_pos_;

		double x_pos_continuous_;
		double y_pos_continuous_;

		/// never set this value directly, use simulation MarkObjectToReprint
		bool must_be_reprinted_ = true;
		const Model* model_ = nullptr;

		//---------------------------------------------------------- Methods
	public:
		GameObject(int x_pos, int y_pos);

		virtual TerminalColor GetColor() const { return nullptr; }
		virtual TerminalColor GetBackColor() const { return nullptr; }
		virtual size_t GetSortingLayer() const { return 100; }
		void Init() { InitModel(); }
		int GetPosX() const { return x_pos_; }
		int GetPosY() const { return y_pos_; }
		int GetMaxPosX()const { return x_pos_ + static_cast<int>(GetModelWidth()) - 1; }
		int GetMaxPosY()const { return y_pos_ + static_cast<int>(GetModelHeight()) - 1; }
		int GetMidPosX() { return GetPosX() + static_cast<int>(GetModelWidth()) / 2; }
		int GetMidPosY() { return GetPosY() + static_cast<int>(GetModelHeight()) / 2; }
		size_t GetModelWidth()const { return model_->GetSizeX(); };
		size_t GetModelHeight()const { return model_->GetSizeY(); }
		const Model& GetModel()const { return *model_; }
		virtual bool CanExitScreenSpace() const = 0;
		static void InsertInListUsingRule(std::shared_ptr<GameObject> obj, std::list<std::shared_ptr<GameObject>>& list, bool(*insert_rule)(std::shared_ptr<GameObject> new_item, std::shared_ptr<GameObject> list_item));
		static void InsertInListUsingRule(std::shared_ptr<GameObject> obj, std::list<std::weak_ptr<GameObject>>& list, bool(*insert_rule)(std::shared_ptr<GameObject> new_item, std::shared_ptr<GameObject> list_item));

	protected:
		virtual void InitModel() = 0;
		virtual double GetGravityScale() const = 0;
		virtual void OnDestroy() {} // called by simulation
		virtual void TryMove(Direction direction, double move_speed);
		void Update()override;
		Model CreteModelUsingChar(char model_char, size_t size_x, size_t size_y) const;
		void SetModel(const Model& new_model);

	private:
		void ResetPartialMovement() { x_pos_continuous_ = x_pos_; y_pos_continuous_ = y_pos_; }
		void ApplyGravity();
		void CALLED_BY_SIM_Move(Direction direction);
	};


}
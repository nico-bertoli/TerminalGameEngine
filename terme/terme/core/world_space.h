#pragma once
#include <terme/utils/direction_utils.h>
#include <terme/sim_entities/fake_collider.h>
#include <nbase_kit/matrix.h>
#include <memory>

#include <cassert>
#include <unordered_set>
#include <set>

namespace terme
{
	class world_space
	{
		//---------------------------------------------------------- Structs
	private:
		struct Cell
		{
			// cell collider, max 1 for cell
			std::weak_ptr<Collider> collider;	

			// all objects in cell, including collider if present
			// (using list cause there are a lot of small sets (2/3 elements max per list usually)
			std::list<std::weak_ptr<game_object>> objects;
		};

		//---------------------------------------------------------- Margins
	public:
		static std::shared_ptr<fake_collider> kWorldMargin;
		static std::shared_ptr<fake_collider> kScreenMargin;

		//---------------------------------------------------------- Fields
	private:
		nbase_kit::Matrix<Cell> space_;
		size_t screen_padding_;
		//---------------------------------------------------------- Methods
	public:
		void Init(int x_size, int y_size, size_t screen_padding);

		bool CanObjectMoveAtDirection(std::shared_ptr<const game_object> obj, Direction direction, std::unordered_set<std::shared_ptr<Collider>>& colliding_objects) const;
		void InsertObject(std::shared_ptr<game_object> obj);
		void RemoveObject(std::shared_ptr<game_object> obj);
		void MoveObject(std::shared_ptr<game_object> obj, Direction direction);
		bool IsCoordinateInsideSpace(int x_pos, int y_pos) const;
		bool IsInsideSpaceX(int x_pos) const;
		bool IsInsideSpaceY(int y_pos) const;

		bool IsCollidersAreaEmpty(int starting_x, int starting_y, size_t width, size_t height, std::unordered_set<std::shared_ptr<Collider>>& out_area_objects) const;
		bool IsCollidersAreaEmpty(int starting_x, int starting_y, size_t width, size_t height) const;

		std::unordered_set<std::shared_ptr<game_object>> GetAreaTopLayerObjects(std::shared_ptr<game_object> obj);
		std::unordered_set<std::shared_ptr<game_object>> GetAreaTopLayerObjects(int starting_x, int starting_y, size_t width, size_t height);

	private:
		void WriteSpace(int x_start, int y_start, size_t width, size_t height, std::shared_ptr<game_object> obj);
		void EraseSpace(int x_start, int y_start, size_t width, size_t height, std::shared_ptr<game_object> obj);
	};
}

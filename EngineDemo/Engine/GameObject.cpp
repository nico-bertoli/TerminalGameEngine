#include "GameObject.h"
#include "TimeHelper.h"
#include "Simulation.h"

using std::shared_ptr;
using std::weak_ptr;

namespace Engine
{
	GameObject::GameObject(int xPos, int yPos) :
		xPos(xPos),
		yPos(yPos),
		xPosContinuous(xPos),
		yPosContinuous(yPos)
	{
		ResetPartialMovement();
	}

	void GameObject::Update()
	{
		ApplyGravity();
	}

	void GameObject::ApplyGravity()
	{
		double gravityScale = GetGravityScale();
		if (gravityScale == 0)
			return;
		if (gravityScale > 0)
			TryMove(Direction::down, gravityScale);
		else
			TryMove(Direction::up, gravityScale);
	}

	void GameObject::TryMove(Direction direction, double moveSpeed)
	{
		if (canMove == false)
			return;

		moveSpeed = abs(moveSpeed);
		double deltaTime = TimeHelper::Instance().GetDeltaTime();

		switch (direction)
		{
		case Direction::up:
			yPosContinuous += moveSpeed * deltaTime;
			break;
		case Direction::down:
			yPosContinuous -= moveSpeed * deltaTime;
			break;
		case Direction::right:
			xPosContinuous += moveSpeed * deltaTime;
			break;
		case Direction::left:
			xPosContinuous -= moveSpeed * deltaTime;
			break;
		}

		if (direction == Direction::left || direction == Direction::right)
		{
			if (round(xPosContinuous) != xPos)
				Simulation::Instance().RequestMovement(std::dynamic_pointer_cast<GameObject>(shared_from_this()), direction, moveSpeed);
		}
		else if (round(yPosContinuous) != yPos)
			Simulation::Instance().RequestMovement(std::dynamic_pointer_cast<GameObject>(shared_from_this()), direction, moveSpeed);
	}

	Model GameObject::CreteModelUsingChar(char modelChar, size_t sizeX, size_t sizeY) const
	{
		Model result;
		result.Resize(sizeX, sizeY);

		for (auto& elem : result)
			elem = modelChar;

		return result;
	}

	void GameObject::SetModel(const Model& newModel)
	{
		if (model == &newModel)
			return;

		model = &newModel;

		Simulation::Instance().MarkAreaToReprint(std::dynamic_pointer_cast<GameObject>(shared_from_this()));
	}

	void GameObject::CALLED_BY_SIM_Move(Direction direction)
	{
		switch (direction)
		{
		case Direction::up:
			++yPos;
			yPosContinuous = yPos;
			break;
		case Direction::down:
			--yPos;
			yPosContinuous = yPos;
			break;
		case Direction::right:
			++xPos;
			xPosContinuous = xPos;
			break;
		case Direction::left:
			--xPos;
			xPosContinuous = xPos;
			break;
		}
		OnMove.Notify(std::dynamic_pointer_cast<GameObject>(shared_from_this()), direction);
	}

	void GameObject::InsertInListUsingRule(shared_ptr<GameObject> obj, std::list<shared_ptr<GameObject>>& list, bool(*InsertRule)(shared_ptr<GameObject> newItem, shared_ptr<GameObject> listItem))
	{
		auto it = list.begin();
		for (; it != list.end(); ++it)
			if(InsertRule(obj,*it))
				break;
		list.insert(it, obj);
	}

	void GameObject::InsertInListUsingRule(shared_ptr<GameObject> obj, std::list<weak_ptr<GameObject>>& list, bool(*InsertRule)(shared_ptr<GameObject> newItem, shared_ptr<GameObject> listItem))
	{
		auto it = list.begin();
		for (; it != list.end(); ++it)
		{
			auto itSharedPtr = it->lock();
			if (itSharedPtr != nullptr && InsertRule(obj, itSharedPtr))
				break;
		}
		list.insert(it, obj);
	}
}
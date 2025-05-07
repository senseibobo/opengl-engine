#pragma once
#include <algorithm>
#include <string>
#include <memory>

class GameObject;
class Transform;

class Component
{
public:
	// constructors
	
	Component()
	{
		gameObject = nullptr;
	}
	
	virtual ~Component() = default;
	//Component(std::string name)
	//{
	//	this->name = name;
	//}

	virtual void Process(float deltaTime);
	virtual void PhysicsProcess(float deltaTime);
	virtual void Draw() const;
	virtual void Start();
	virtual void OnAddedd(GameObject* gameObject);
	virtual void OnRemoved();
	virtual void OnDestroyed();
	//std::string name;
	GameObject* GetGameObject() const;

private:
	GameObject* gameObject;
};


#pragma once
#include "Vector2.h"
#include "Component.h"
#include "Transform.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>

class GameObject
{
public:


	// constructors
	GameObject()
	{
		transform = std::make_shared<Transform>();
	}
	~GameObject()
	{

	}


	// set
	// get
	std::shared_ptr<Transform> GetTransform();

	// other
	void Start();
	void Process(float deltaTime);
	void PhysicsProcess(float deltaTime);
	void Draw() const;
	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::shared_ptr<Component> component);

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must derive from Component");
		for (auto& component : components)
			if (auto casted = std::dynamic_pointer_cast<T>(component))
				return casted;
		return nullptr;
	}
private:
	std::vector<std::shared_ptr<Component>> components;
	std::shared_ptr<Transform> transform;
};
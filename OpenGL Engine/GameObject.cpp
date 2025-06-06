#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"


void GameObject::Start()
{
	for (auto component : components)
	{
		component->Start();
	}
}

void GameObject::Process(float deltaTime)
{
	for (auto component : components)
	{
		component->Process(deltaTime);
	}
}

void GameObject::PhysicsProcess(float deltaTime)
{
	for (auto component : components)
	{

		component->PhysicsProcess(deltaTime);
	}
}

void GameObject::Draw() const
{
	for (auto component : components)
	{
		component->Draw();
	}
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{

	components.push_back(component);
	component->OnAddedd(this);
}

void GameObject::RemoveComponent(std::shared_ptr<Component> component)
{
	component->OnRemoved();
	auto begin = components.begin();
	auto end = components.end();
	auto iter = std::find(begin, end, component);
	components.erase(iter);
}

void GameObject::RemoveAllComponents()
{

	for (const auto& component : components)
	{
		if (!component) continue;
		std::cout << "Removing all components heree!\n";
		component->OnRemoved();
		component->OnDestroyed();
	}
	components.clear();
}

void GameObject::Destroy()
{
	Scene::GetCurrent()->DestroyObject(this);
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	return transform;
}

std::vector<std::shared_ptr<Component>>& GameObject::GetComponents()
{
	return components;
}

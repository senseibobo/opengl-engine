#include "Component.h"
#include "GameObject.h"


void Component::Process(float deltaTime) {}
void Component::PhysicsProcess(float deltaTime) {}
void Component::Draw() const {}
void Component::Start() {}
void Component::OnRemoved() {}
void Component::OnDestroyed() {}

void Component::OnAddedd(GameObject* gameObject) 
{
	this->gameObject = gameObject;
}

GameObject* Component::GetGameObject() const
{
	return this->gameObject;
}

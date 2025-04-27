#include "PhysicsCollisionShape.h"

void PhysicsCollisionShape::SetPosition(Vector2 newPosition)
{
	this->position = newPosition;
}

void PhysicsCollisionShape::SetRotation(float newRotation)
{
	this->rotation = newRotation;
}

void PhysicsCollisionShape::SetScale(Vector2 newScale)
{
	this->scale = newScale;
}

Vector2 PhysicsCollisionShape::GetPosition() const
{
	return this->position;
}

float PhysicsCollisionShape::GetRotation() const
{
	return this->rotation;
}

Vector2 PhysicsCollisionShape::GetScale() const
{
	return this->scale;
}

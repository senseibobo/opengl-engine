#include "Transform.h"

Vector2 Transform::GetPosition() const
{
	return position;
}

float Transform::GetRotation() const
{
	return this->rotation;
}

Vector2 Transform::GetScale() const
{
	return this->scale;
}

void Transform::Translate(Vector2 pos)
{
	std::cout << "Moving " << pos.y << "\n";
	this->position += pos;
}

void Transform::Rotate(float angle)
{
	this->rotation += angle;
}


void Transform::SetPosition(Vector2 newPosition)
{
	this->position = newPosition;
}

void Transform::SetRotation(float newRotation)
{
	this->rotation = newRotation;
}

void Transform::SetScale(Vector2 newScale)
{
	this->scale = newScale;
}
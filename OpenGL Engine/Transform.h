#pragma once
#include <iostream>
#include "Component.h"
#include "Vector2.h"
class Transform : public Component
{
public:

	// constructor
	Transform() : Component()
	{
		position = Vector2(0.0,0.0);
		rotation = 0.0;
		scale = Vector2(1.0,1.0);
	}

	// set 
	void SetPosition(Vector2 newPosition);
	void SetRotation(float newRotation);
	void SetScale(Vector2 newScale);

	// get 
	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;

	// other
	void Translate(Vector2 pos);
	void Rotate(float angle);

private:
	Vector2 position;
	float rotation;
	Vector2 scale;
};


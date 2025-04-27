#pragma once
#include <iostream>
#include "Rect2.h"
#include "Transform.h"

class PhysicsCircleShape;
class PhysicsRectangleShape;

class PhysicsCollisionShape
{
public:
	virtual bool CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform) const = 0;

	virtual bool CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform) const = 0;
	virtual bool CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform) const = 0;

	void SetPosition(Vector2 newPosition);
	void SetRotation(float newRotation);
	void SetScale(Vector2 newScale);

	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;
private:
	Vector2 position;
	float rotation;
	Vector2 scale;
};


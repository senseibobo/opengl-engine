#pragma once
#include <iostream>
#include "Rect2.h"
#include "Transform.h"
#include "CollisionData.h"

class PhysicsCircleShape;
class PhysicsRectangleShape;

class PhysicsCollisionShape
{
public:
	virtual CollisionData CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const = 0;

	virtual CollisionData CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const = 0;
	virtual CollisionData CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const = 0;

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


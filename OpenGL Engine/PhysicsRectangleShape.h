#pragma once
#include "PhysicsCollisionShape.h"

class PhysicsCircleShape;

class PhysicsRectangleShape : public PhysicsCollisionShape
{
public:
	CollisionData CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const override;

	CollisionData CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const override;
	CollisionData CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const override;

	Rect2 GetRect() const;

	void SetPosition(Vector2 newPosition);
	void SetSize(Vector2 newSize);

private:
	Vector2 position; // rectangle is centered
	Vector2 size;
};


#pragma once
#include "PhysicsCollisionShape.h"

class PhysicsCircleShape;

class PhysicsRectangleShape : public PhysicsCollisionShape
{
public:
	bool CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform) const override;

	bool CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform) const override;
	bool CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform) const override;

	Rect2 GetRect() const;

	void SetPosition(Vector2 newPosition);
	void SetSize(Vector2 newSize);

private:
	Vector2 position; // rectangle is centered
	Vector2 size;
};


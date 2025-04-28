#pragma once
#include "PhysicsCollisionShape.h"

class PhysicsRectangleShape;

class PhysicsCircleShape : public PhysicsCollisionShape
{
public:
	bool CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const override;
	bool CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const override;
	bool CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const override;
	bool ContainsPoint(const Vector2& point) const;

	void SetRadius(float newRadius);
	float GetRadius() const;
private:
	float radius;
};


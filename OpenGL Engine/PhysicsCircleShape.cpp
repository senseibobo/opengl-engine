#include "PhysicsCircleShape.h"
#include "PhysicsRectangleShape.h"

bool PhysicsCircleShape::CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform) const
{
	return shape.CollideWithCircle(*this, otherTransform, thisTransform);
}

bool PhysicsCircleShape::CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform) const
{
	const float otherScale = circle.GetScale().x * otherTransform->GetScale().x;
	const float thisScale = GetScale().x*thisTransform->GetScale().x;
	const float otherRadius = GetRadius();
	const float thisRadius = GetRadius();
	if (!circle.GetScale().IsUniform() || !GetScale().IsUniform())
	{
		std::cout << "Non-uniform scaled collision for circles isn't supported!\n";
		return false;
	}
	const Vector2 thisPosition = GetPosition() + thisTransform->GetPosition();
	const Vector2 otherPosition = circle.GetPosition() + otherTransform->GetPosition();
	float distance = thisPosition.DistanceTo(otherPosition);
	return distance <= thisScale * thisRadius + otherScale * otherRadius;
}

bool PhysicsCircleShape::CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform) const
{
	return rectangle.CollideWithCircle(*this, otherTransform, thisTransform);
}

bool PhysicsCircleShape::ContainsPoint(const Vector2& point) const
{
	float distance = GetPosition().DistanceTo(point);
	return distance < GetRadius();
}

void PhysicsCircleShape::SetRadius(float newRadius)
{
	this->radius = newRadius;
}

float PhysicsCircleShape::GetRadius() const
{
	return this->radius;
}



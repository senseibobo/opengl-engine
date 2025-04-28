#include "PhysicsCircleShape.h"
#include "PhysicsRectangleShape.h"

CollisionData PhysicsCircleShape::CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{
	return shape.CollideWithCircle(*this, otherTransform, thisTransform, -thisMotion);
}

CollisionData PhysicsCircleShape::CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{
	const float otherScale = circle.GetScale().x * otherTransform->GetScale().x;
	const float thisScale = GetScale().x*thisTransform->GetScale().x;
	const float otherRadius = GetRadius();
	const float thisRadius = GetRadius();
	if (!circle.GetScale().IsUniform() || !GetScale().IsUniform())
	{
		std::cout << "Non-uniform scaled collision for circles isn't supported!\n";
		return CollisionData();
	}
	const Vector2 thisPosition = GetPosition() + thisTransform->GetPosition();
	const Vector2 otherPosition = circle.GetPosition() + otherTransform->GetPosition();
	float distanceBeforeMotion = thisPosition.DistanceTo(otherPosition);
	float distanceAfterMotion = (thisPosition + thisMotion).DistanceTo(otherPosition);
	float collisionDistance = thisScale * thisRadius + otherScale * otherRadius;
	if (distanceAfterMotion <= collisionDistance)
	{
		Vector2 normal = (thisPosition - otherPosition).Normalized();
		float distanceLeft = distanceBeforeMotion - collisionDistance;
		Vector2 motionLeft = thisMotion.Normalized() * distanceLeft;
		return CollisionData(normal, motionLeft);
	}
	else
	{
		return CollisionData();
	}
}

CollisionData PhysicsCircleShape::CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{
	return rectangle.CollideWithCircle(*this, otherTransform, thisTransform, -thisMotion);
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



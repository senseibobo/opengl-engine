#include "PhysicsRectangleShape.h"
#include "PhysicsCircleShape.h"

CollisionData PhysicsRectangleShape::CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{
	return shape.CollideWithRectangle(*this, otherTransform, thisTransform, -thisMotion);
}

CollisionData PhysicsRectangleShape::CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{
	Rect2 rectBeforeMotion = GetRect().Transformed(thisTransform);
	Rect2 rectAfterMotion = rectBeforeMotion;
	rectAfterMotion.position += thisMotion;
	Vector2 closestPointBeforeMotion = rectBeforeMotion.GetClosestPointTo(circle.GetPosition());
	Vector2 closestPointAfterMotion = rectAfterMotion.GetClosestPointTo(circle.GetPosition());
	float collisionDistance = circle.GetRadius();
	float distanceBeforeMotion = closestPointBeforeMotion.DistanceTo(circle.GetPosition());
	float distanceAfterMotion = closestPointAfterMotion.DistanceTo(circle.GetPosition());

	if (distanceAfterMotion < collisionDistance)
	{
		Vector2 normal = (closestPointAfterMotion - circle.GetPosition()).Normalized();
		Vector2 collisionPoint = closestPointAfterMotion;
		collisionPoint.SetLength(circle.GetRadius());
		Vector2 motionLeft = (closestPointAfterMotion - collisionPoint);
		return CollisionData(normal, motionLeft);
	}
	else
		return CollisionData();
}

// TODO
CollisionData PhysicsRectangleShape::CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{
	Rect2 r1 = this->GetRect().Transformed(thisTransform);
	Rect2 r2 = rectangle.GetRect().Transformed(otherTransform);
	return !(
		r1.position.x + r1.size.x < r2.position.x ||
		r1.position.y + r1.size.y < r2.position.y ||
		r1.position.x > r2.position.x + r2.size.x ||
		r1.position.y > r2.position.y + r2.size.y);
}

Rect2 PhysicsRectangleShape::GetRect() const
{
	return Rect2(GetPosition()-(size / 2.0f), size);
}

void PhysicsRectangleShape::SetPosition(Vector2 newPosition)
{
	this->position = newPosition;
}

void PhysicsRectangleShape::SetSize(Vector2 newSize)
{
	this->size = newSize;
}



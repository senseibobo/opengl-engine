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

CollisionData PhysicsRectangleShape::CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform, Vector2 thisMotion) const
{

	if (thisMotion.Length() == 0.0) return CollisionData();
	Rect2 r1BeforeMotion = this->GetCenteredRect().Transformed(thisTransform);
	Rect2 r1AfterMotion = r1BeforeMotion;
	r1AfterMotion.position += thisMotion;
	Rect2 r2 = rectangle.GetCenteredRect().Transformed(otherTransform);
	//bool collidedXLeft = r1AfterMotion.position.x + r1AfterMotion.size.x < r2.position.x;
	//bool collidedXRight = r1AfterMotion.position.x > r2.position.x + r2.size.x;
	//bool collidedYUp = r1AfterMotion.position.y + r1AfterMotion.size.y < r2.position.y;
	//bool collidedYDown = r1AfterMotion.position.y > r2.position.y + r2.size.y;

	Vector2 diff = (r1AfterMotion.position - r2.position);
	Vector2 diffAbsolute = diff.Absolute();
	Vector2 sizes = (r2.size + r1AfterMotion.size) / 2.0;
	Vector2 collisionDistance = diffAbsolute - sizes;
	
	Vector2 normal;
	Vector2 motionLeft;

	if (collisionDistance.x < 0.0 && collisionDistance.y < 0.0)
	{
		if (collisionDistance.x > collisionDistance.y)
		{
			normal = Vector2(-thisMotion.x, 0.0).Normalized();
			motionLeft.x = normal.x * (thisMotion.x + collisionDistance.x);
		}
		else
		{
			normal = Vector2(0.0, thisMotion.y).Normalized();
			motionLeft.y = -normal.y * (thisMotion.y + collisionDistance.y);
		}
		return CollisionData(normal, motionLeft);
	}

	else
		return CollisionData();
}

Rect2 PhysicsRectangleShape::GetRect() const
{
	return Rect2(GetPosition() - (size / 2.0f), size);
}


Rect2 PhysicsRectangleShape::GetCenteredRect() const
{
	return Rect2(GetPosition(), size);
}

void PhysicsRectangleShape::SetPosition(Vector2 newPosition)
{
	this->position = newPosition;
}

void PhysicsRectangleShape::SetSize(Vector2 newSize)
{
	this->size = newSize;
}



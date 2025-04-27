#include "PhysicsRectangleShape.h"
#include "PhysicsCircleShape.h"

bool PhysicsRectangleShape::CollideWith(const PhysicsCollisionShape& shape, Transform* thisTransform, Transform* otherTransform) const
{
	return shape.CollideWithRectangle(*this, otherTransform, thisTransform);
}

bool PhysicsRectangleShape::CollideWithCircle(const PhysicsCircleShape& circle, Transform* thisTransform, Transform* otherTransform) const
{
	const Rect2& rect = GetRect().Transformed(thisTransform);
	Vector2 closestPoint = rect.GetClosestPointTo(circle.GetPosition());
	if(closestPoint.DistanceTo(circle.GetPosition()) < circle.GetRadius()) 
		return true;
}

bool PhysicsRectangleShape::CollideWithRectangle(const PhysicsRectangleShape& rectangle, Transform* thisTransform, Transform* otherTransform) const
{
	std::cout << "rect rect";;
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



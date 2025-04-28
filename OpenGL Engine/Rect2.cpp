#include "Rect2.h"
#include "Transform.h"

Rect2::Rect2()
{
	position = Vector2();
	size = Vector2();
}

Rect2::Rect2(const Vector2& position, const Vector2& size)
{
	this->position = position;
	this->size = size;
}

Vector2 Rect2::GetClosestPointTo(const Vector2& point) const
{
	Vector2 closestPoint;
	if (point.x < position.x) closestPoint.x = position.x;
	else if (point.x > position.x + size.x) closestPoint.x = position.x + size.x;
	else closestPoint.x = point.x;
	if (point.y < position.y) closestPoint.y = position.y;
	else if (point.y > position.y + size.y) closestPoint.y = position.y + size.y;
	else closestPoint.y = point.y;
	return closestPoint;
}

bool Rect2::ContainsPoint(const Vector2& point) const
{
	return point.x > position.x && point.y > position.y &&
		point.x < position.x + size.x &&
		point.y < position.y + size.y;
}

Rect2 Rect2::Transformed(const Transform* transform) const
{
	return Rect2(position + transform->GetPosition(), size * transform->GetScale());
}

Vector2 Rect2::GetCenter() const
{
	return position + size/2.0;
}

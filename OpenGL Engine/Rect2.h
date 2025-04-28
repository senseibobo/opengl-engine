#pragma once
#include "Vector2.h"
#include <math.h>

class Transform;

class Rect2
{
public:
	Rect2();
	Rect2(const Vector2& position, const Vector2& size);
	Vector2 position;
	Vector2 size;

	Vector2 GetClosestPointTo(const Vector2& point) const;
	bool ContainsPoint(const Vector2& point) const;
	Rect2 Transformed(const Transform* transform) const;
	Vector2 GetCenter() const;
};


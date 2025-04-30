#pragma once
#include "Vector2.h"
class CollisionData
{
public:
	CollisionData()
	{
		this->collided = false;
	}

	CollisionData(const Vector2& normal, const Vector2& motionLeft)
	{
		this->collided = true;
		this->normal = normal;
		this->motionLeft = motionLeft;
	}

	bool IsCollision();
	Vector2 GetNormal();
	Vector2 GetMotionLeft();
	bool IsWallCollision();
	bool IsCeilingCollision();
	bool IsFloorCollision();
	bool IsDownwardSlopeCollision();
	bool IsUpwardSlopeCollision();
private:
	bool collided;
	Vector2 normal;
	Vector2 motionLeft;
};


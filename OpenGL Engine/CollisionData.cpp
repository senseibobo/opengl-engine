#include "CollisionData.h"

bool CollisionData::IsCollision()
{
	return this->collided;
}

Vector2 CollisionData::GetNormal()
{
	return this->normal;
}

Vector2 CollisionData::GetMotionLeft()
{
	return this->motionLeft;
}


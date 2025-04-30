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

bool CollisionData::IsWallCollision()
{
	return fabsf(this->GetNormal().x) > 0.7;
}

bool CollisionData::IsCeilingCollision()
{
	return this->GetNormal().y < -0.7;;
}

bool CollisionData::IsFloorCollision()
{
	return this->GetNormal().y > 0.7;
}

bool CollisionData::IsDownwardSlopeCollision()
{
	const Vector2& normal = this->GetNormal();
	return fabsf(normal.x) > 0.3 && normal.y > 0.3;
}

bool CollisionData::IsUpwardSlopeCollision()
{
	const Vector2& normal = this->GetNormal();
	return fabsf(normal.x) > 0.3 && normal.y < -0.3;
}


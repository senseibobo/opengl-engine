#include "Physics.h"
#include "Collision.h"

std::vector<std::shared_ptr<Collision>> Physics::collisions;

bool Physics::CheckAnyCollision(std::shared_ptr<Collision> collision, Vector2 motion)
{
	for (auto otherCollision : collisions)
	{
		if (otherCollision == collision) continue;
		if (collision->CheckCollision(otherCollision)) {
			return true;
		}
	}
	return false;
}

void Physics::RemoveCollision(std::shared_ptr<Collision> collision)
{
	auto begin = collisions.begin();
	auto end = collisions.end();
	auto iter = std::find(begin, end, collision);
	collisions.erase(iter);
}

std::shared_ptr<Collision> Physics::CreateCollision()
{
	std::shared_ptr<Collision> collision = std::make_shared<Collision>();
	collisions.push_back(collision);
	return collision;
}


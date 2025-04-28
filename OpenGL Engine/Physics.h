#pragma once
#include <vector>
#include "PhysicsCollisionShape.h"

class Collision;

class Physics
{
public:
	Physics() = delete;

	static bool CheckAnyCollision(std::shared_ptr<Collision> collision, Vector2 motion);
	static void RemoveCollision(std::shared_ptr<Collision> collision);
	static std::shared_ptr<Collision> CreateCollision();
private:
	static std::vector<std::shared_ptr<Collision>> collisions;
};


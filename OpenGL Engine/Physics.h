#pragma once
#include <vector>
#include "PhysicsCollisionShape.h"

class Collision;

class Physics
{
public:
	Physics() = delete;

	static bool CheckAnyCollision(std::shared_ptr<Collision> collision);
	static void RemoveCollision(std::shared_ptr<Collision> collision);
	static std::shared_ptr<Collision> CreateCollision();
private:
	static void AddCollision(std::shared_ptr<Collision> collision);
	static std::vector<std::shared_ptr<Collision>> collisions;
};


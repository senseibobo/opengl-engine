#pragma once
#include <type_traits>
#include "Component.h"
#include "Physics.h"
class Collision : public Component
{
public:
	// set
	void SetShape(std::shared_ptr<PhysicsCollisionShape> shape);
	void SetLayer(int newLayer);
	
	// get
	int GetLayer() const;
	std::shared_ptr<PhysicsCollisionShape> GetShape() const;

	// other
	CollisionData CheckCollision(std::shared_ptr<Collision> other, Vector2 motion);
private:
	int layer;
	std::shared_ptr<PhysicsCollisionShape> shape;
};


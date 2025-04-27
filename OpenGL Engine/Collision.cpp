#include "Collision.h"
#include "GameObject.h"

void Collision::SetShape(std::shared_ptr<PhysicsCollisionShape> shape)
{
	this->shape = shape;
}

void Collision::SetLayer(int newLayer)
{
	this->layer = newLayer;
}

int Collision::GetLayer() const
{
	return this->layer;
}

std::shared_ptr<PhysicsCollisionShape> Collision::GetShape() const
{
	return this->shape;;
}

bool Collision::CheckCollision(std::shared_ptr<Collision> other)
{
	if (GetLayer() != other->GetLayer()) return false;
	Transform* thisTransform = GetGameObject()->GetTransform().get();
	Transform* otherTransform = other->GetGameObject()->GetTransform().get();
	return shape->CollideWith(*other->GetShape(), thisTransform, otherTransform);
}


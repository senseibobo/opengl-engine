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

CollisionData Collision::CheckCollision(std::shared_ptr<Collision> other, Vector2 motion)
{
	if (GetLayer() != other->GetLayer()) return CollisionData();
	Transform* thisTransform = GetGameObject()->GetTransform().get();
	GameObject* otherGameObject = other->GetGameObject();
	Transform* otherTransform = otherGameObject->GetTransform().get();
	return shape->CollideWith(*other->GetShape(), thisTransform, otherTransform, motion);
}


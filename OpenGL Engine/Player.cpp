#include "Player.h"
#include "GameObject.h"
#include "Collision.h"
#include "Input.h"
#include <cassert>

void Player::Start()
{
	collision = GetGameObject()->GetComponent<Collision>();
	transform = GetGameObject()->GetTransform();
}

void Player::Process(float deltaTime)
{
	GetGameObject()->GetTransform()->Rotate(deltaTime);
}

void Player::PhysicsProcess(float deltaTime)
{
	if (collision != nullptr && Physics::CheckAnyCollision(collision))
		velocity = Vector2();
	else {
		velocity.x = Input::GetAxis("move_left", "move_right")*50.0f;
		velocity.y -= deltaTime * 30.0f;
	}
	transform->Translate(velocity * deltaTime);

}

void Player::SetMovementSpeed(float newMovementSpeed)
{
	movementSpeed = newMovementSpeed;
}

void Player::SetJumpHeight(float newJumpHeight)
{
	jumpHeight = newJumpHeight;
}

void Player::SetVelocity(Vector2 newVelocity)
{
	this->velocity = newVelocity;
}

Vector2 Player::GetVelocity() const
{
	return this->velocity;
}

float Player::GetMovementSpeed() const
{
	return movementSpeed;
}

float Player::GetJumpHeight() const
{
	return this->jumpHeight;
}

void Player::AddVelocity(Vector2 addedVelocity)
{
	this->velocity += addedVelocity;
}

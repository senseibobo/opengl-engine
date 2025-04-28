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
	//GetGameObject()->GetTransform()->Rotate(deltaTime);
}

void Player::PhysicsProcess(float deltaTime)
{
	switch (state)
	{
	case State::FALLING:
	{
		ProcessFalling(deltaTime);
		break;
	}
	}
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

void Player::SetState(State newState)
{
	this->state = newState;
}

void Player::SetGravity(float newGravity)
{
	this->gravity = newGravity;
}

float Player::GetGravity() const
{
	return this->gravity;
}

Player::State Player::GetState() const
{
	return this->state;
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

CollisionData Player::MoveAndCollide(const Vector2& moveVector)
{
	CollisionData collisionData = Physics::CheckAnyCollision(collision, moveVector);
	if (collisionData.IsCollision())
	{
		Vector2 motionLeft = collisionData.GetMotionLeft();
		if (motionLeft.Length() < 0.01) motionLeft = Vector2();
		Vector2 moved = moveVector - motionLeft;
	}
	else 
	{
		transform->Translate(moveVector);
	}
	return collisionData;
}

void Player::ProcessWalking(float deltaTime)
{

}

void Player::ProcessFalling(float deltaTime)
{
	velocity.y -= deltaTime * gravity;
	CollisionData collisionData = MoveAndCollide(velocity * deltaTime);
	if (collisionData.IsCollision())
	{
		std::cout << collisionData.GetNormal().x << " " << collisionData.GetNormal().y << "\n";
		if (abs(collisionData.GetNormal().x) > 0.7) // hit wall
		{
			velocity.x = -velocity.x;
		}
		else if (collisionData.GetNormal().y > 0.7) // hit floor
		{
			SetState(State::WALKING);
		}
		else // hit ceiling
		{
			velocity.y = 0;
		}
	}

}

void Player::ProcessJumping(float deltaTime)
{

}


#include "Player.h"
#include "GameObject.h"
#include "Collision.h"
#include "Input.h"
#include "Sprite.h"
#include <cassert>
#include "Game.h"
#include "PhysicsRectangleShape.h"

Player* Player::Instance = nullptr;

void Player::Start()
{
	Instance = this;
	collision = GetGameObject()->GetComponent<Collision>();
	transform = GetGameObject()->GetTransform();
	sprite = GetGameObject()->GetComponent<Sprite>();
}

void Player::Process(float deltaTime)
{
	if (Input::GetActionPressed("platform") and trampolinesLeft > 0)
	{
		trampolinesLeft--;
		std::shared_ptr<GameObject> ground = Game::Instance->scene->AddObject();
		std::shared_ptr<Transform> transform = ground->GetTransform();
		transform->SetPosition(GetGameObject()->GetTransform()->GetPosition() - Vector2(0, 50.0));
		//transform->SetScale();
		std::shared_ptr<Collision> collisionComponent = Physics::CreateCollision();
		std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>();
		spriteComponent->SetTiled(true);
		spriteComponent->SetTileSize(Vector2(40, 40));
		ground->AddComponent(collisionComponent);
		ground->AddComponent(spriteComponent);

		std::shared_ptr<PhysicsRectangleShape> collisionShape = std::make_shared<PhysicsRectangleShape>();
		collisionComponent->SetShape(std::static_pointer_cast<PhysicsCollisionShape>(collisionShape));

		std::shared_ptr<Texture> texture = spriteComponent->LoadAndSetTexture("textures/brickTile.png");
		collisionShape->SetSize(texture->GetSize());
		ground->Start();
	}
}

void Player::PhysicsProcess(float deltaTime)
{
	switch (state)
	{
	case State::FALLING: ProcessFalling(deltaTime); break;
	case State::JUMPING: ProcessJumping(deltaTime); break;
	case State::WALKING: ProcessWalking(deltaTime); break;
	case State::CHARGING: ProcessCharging(deltaTime); break;
	}
	if (Input::GetAction("reset"))
	{
		velocity = Vector2(100,0);
		transform->SetPosition(Vector2(400, 500));
		SetState(State::FALLING);
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
		Vector2 motionLeft = collisionData.GetMotionLeft() + collisionData.GetNormal()*0.05;
		transform->Translate(motionLeft);
	}
	else 
	{
		transform->Translate(moveVector);
	}
	return collisionData;
}

void Player::ProcessWalking(float deltaTime)
{
	CollisionData downCollision = Physics::CheckAnyCollision(collision, Vector2(0.0, -10.0));
	if (!downCollision.IsCollision())
	{
		SetState(State::FALLING);
	}
	else {
		int moveInput = Input::GetAxis("move_left", "move_right");
		if (moveInput != 0)
		{
			facing = moveInput;
			sprite->SetFlipHorizontal(facing < 0);
		}
		velocity.x = moveInput * movementSpeed;
		velocity.y = 0.0;
		CollisionData collision = MoveAndCollide(velocity * deltaTime);
		//if(collision.IsCollision())
		if (Input::GetAction("jump"))
		{
			velocity = Vector2();
			jumpChargeAmount = 0.0;
			SetState(State::CHARGING);
		}
	}
}

void Player::ProcessFalling(float deltaTime)
{
	velocity.y -= deltaTime * gravity;
	CollisionData collisionData = MoveAndCollide(velocity * deltaTime);
	if (collisionData.IsCollision())
	{
		if (collisionData.IsWallCollision()) // hit wall
		{
			velocity.x = -velocity.x;
		}
		else if (collisionData.IsFloorCollision()) // hit floor
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
	velocity.y -= gravity * deltaTime;
	CollisionData collision = MoveAndCollide(velocity * deltaTime);
	if (collision.IsFloorCollision())
	{
		SetState(State::WALKING);
	}
	else if (collision.IsWallCollision())
	{
		velocity.x = -velocity.x;
		SetState(State::FALLING);
	}
	else if (collision.IsCeilingCollision())
	{
		velocity.y = 0.0;
		SetState(State::FALLING);
	}
}

void Player::ProcessCharging(float deltaTime)
{
	velocity = Vector2();
	jumpChargeAmount += deltaTime;
	if (jumpChargeAmount > maxJumpChargeAmount) jumpChargeAmount = maxJumpChargeAmount;
	if (!Input::GetAction("jump"))
	{
		velocity.x = (baseHorizontalJump) * jumpHeight * facing;
		velocity.y = (baseVerticalJump + jumpChargeAmount) * jumpHeight * 2.0;
		jumpChargeAmount = 0.0;
		SetState(State::JUMPING);
	}
}


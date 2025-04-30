#pragma once
#include "Component.h"
#include "Physics.h"
class Sprite;

class Player : public Component
{
public:

	enum State {
		JUMPING,
		WALKING,
		FALLING,
		CHARGING
	};

	Player()
	{
		state = State::FALLING;
		movementSpeed = 250.0;
		jumpHeight = 500.0;
		velocity = Vector2(100.0, 0.0);
		gravity = 1200.0;
		jumpChargeAmount = 0.0;
		maxJumpChargeAmount = 1.0;
		baseHorizontalJump = 0.7;
		baseVerticalJump = 0.05;
		facing = 1;
	}


	// override 
	void Start() override;
	void Process(float deltaTime) override;
	void PhysicsProcess(float deltaTime) override;
	
	// set
	void SetState(State newState);
	void SetVelocity(Vector2 newVelocity);
	void SetMovementSpeed(float newMovementSpeed);
	void SetJumpHeight(float newJumpHeight);
	void SetGravity(float newGravity);

	// get
	State GetState() const;
	Vector2 GetVelocity() const;
	float GetMovementSpeed() const;
	float GetJumpHeight() const;
	float GetGravity() const;

	// other
	void AddVelocity(Vector2 addedVelocity);
	CollisionData MoveAndCollide(const Vector2& moveVector);
	void ProcessWalking(float deltaTime);
	void ProcessFalling(float deltaTime);
	void ProcessJumping(float deltaTime);
	void ProcessCharging(float deltaTime);

private:
	State state;
	int facing;
	float movementSpeed;
	float jumpHeight;
	float jumpChargeAmount;
	float maxJumpChargeAmount;
	float gravity;
	float baseHorizontalJump;
	float baseVerticalJump;
	Vector2 velocity;
	std::shared_ptr<Collision> collision;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Sprite> sprite;
};


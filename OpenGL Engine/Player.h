#pragma once
#include "Component.h"
#include "Physics.h"
class Player : public Component
{
public:

	enum State {
		JUMPING,
		WALKING,
		FALLING
	};

	Player()
	{
		state = State::FALLING;
		movementSpeed = 100.0;
		jumpHeight = 100.0;
		velocity = Vector2(100.0, 0.0);
		gravity = 100.0;
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

private:
	State state;
	float movementSpeed;
	float jumpHeight;
	float gravity;
	Vector2 velocity;
	std::shared_ptr<Collision> collision;
	std::shared_ptr<Transform> transform;
};


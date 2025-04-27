#pragma once
#include "Component.h"
#include "Physics.h"
class Player : public Component
{
public:
	// override 
	void Start() override;
	void Process(float deltaTime) override;
	void PhysicsProcess(float deltaTime) override;
	
	// set
	void SetMovementSpeed(float newMovementSpeed);
	void SetJumpHeight(float newJumpHeight);
	void SetVelocity(Vector2 newVelocity);

	// get
	Vector2 GetVelocity() const;
	float GetMovementSpeed() const;
	float GetJumpHeight() const;

	// other
	void AddVelocity(Vector2 addedVelocity);

private:
	float movementSpeed;
	float jumpHeight;
	std::shared_ptr<Collision> collision;
	std::shared_ptr<Transform> transform;
	Vector2 velocity;
};


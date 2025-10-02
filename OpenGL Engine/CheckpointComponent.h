#pragma once
#include "Component.h"
#include "Player.h"
class CheckpointComponent : public Component
{
public:
	void PhysicsProcess(float deltaTime) override;
private:
	bool saved = false;
};


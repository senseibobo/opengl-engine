#pragma once
#include "Camera.h"
class GameCamera : public Camera
{
public:
	GameCamera() : Camera()
	{
		level = 0;
	}
	void Process(float deltaTime) override;
	void UpdateView() override;
private:
	int level;
};


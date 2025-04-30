#pragma once
#include "Component.h"
#include "View.h"

class Camera : public Component
{
public:
	Camera()
	{
		level = 0;
		current = false;
		if (currentCamera == nullptr)
			SetCurrent();
	}
	void SetCurrent();
	static Camera* GetCurrentCamera();
	void Process(float deltaTime) override;
	void UpdateView();
private:
	static Camera* currentCamera;
	bool current;
	int level;
};


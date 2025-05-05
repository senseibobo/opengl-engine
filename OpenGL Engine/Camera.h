#pragma once
#include "Component.h"
#include "View.h"

class Camera : public Component
{
public:
	Camera()
	{
		current = false;
		if (currentCamera == nullptr)
			SetCurrent();
	}
	void SetCurrent();
	static Camera* GetCurrentCamera();
	void Process(float deltaTime) override;
	virtual void UpdateView();
private:
	static Camera* currentCamera;
	bool current;
};


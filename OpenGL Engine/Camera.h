#pragma once
#include "Component.h"
#include "glut.h"
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
	void UpdateView(int width, int height);
private:
	static Camera* currentCamera;


	int windowWidth;
	int windowHeight;
	bool current;
	int level;
};


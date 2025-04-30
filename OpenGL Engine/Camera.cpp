#include "Camera.h"
#include "GameObject.h"

Camera* Camera::currentCamera = nullptr;

void Camera::SetCurrent()
{
	current = true;
	currentCamera = this;
}

Camera* Camera::GetCurrentCamera()
{
	return currentCamera;
}

void Camera::Process(float deltaTime)
{
	std::shared_ptr<Transform> transform = GetGameObject()->GetTransform();
	int oldLevel = level;
	level = ((int)transform->GetPosition().y) / 600;
	if (oldLevel != level)
	{
		UpdateView(windowWidth, windowHeight);
	}
}

void Camera::UpdateView(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, windowWidth, windowWidth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, level * 600, 600 + level * 600);
	glMatrixMode(GL_MODELVIEW);
}
